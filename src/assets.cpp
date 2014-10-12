#include "assets.h"
#include "game.h"
#include "sdl_exception.h"
#include <SDL_image.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

namespace superpaflaballe {

    assets::assets(game& game)
    : game_(game) {
        pathPrefixes_.push_back("../assets/");
        pathPrefixes_.push_back(PREFIX "/games/superpaflaballe/");
        int flags = IMG_INIT_PNG;
        int initted = IMG_Init(flags);
        if ((initted & flags) != flags) {
            throw sdl_exception();
        }
    }

    assets::~assets() {
        IMG_Quit();
    }

    std::shared_ptr< SDL_Texture > assets::texture(const std::string& path) {

        boost::filesystem::path fspath(path);
        for (auto& prefix : pathPrefixes_) {
            boost::filesystem::path fsprefix(prefix);
            auto texture = load_texture((fsprefix / fspath).string());
            if (texture) {
                return texture;
            }
        }
        throw std::runtime_error("Cannot load texture " + path);
    }

    std::shared_ptr< SDL_Texture > assets::load_texture(const std::string path) {
        return std::shared_ptr< SDL_Texture >(IMG_LoadTexture(game_.renderer(), path.c_str()), SDL_DestroyTexture);
    }

    std::shared_ptr< nanim::collection > assets::animations(const std::string& path) {
        for (auto& prefix : pathPrefixes_) {
            try {
                return load_json_nanim(prefix + path);
            } catch (...) {
            }
        }
        throw std::runtime_error("Cannot load animations " + path);
    }

    std::shared_ptr<nanim::collection> assets::load_json_nanim(const std::string& path) {
        using boost::property_tree::ptree;
        if(!boost::filesystem::exists(path)) {
            return nullptr;
        }
        ptree pt_nanim;
        boost::property_tree::read_json(path, pt_nanim);
        boost::filesystem::path parent_path = boost::filesystem::path(path).parent_path();
        auto collec = std::make_shared<nanim::collection>();

        for (auto& pt_animation : pt_nanim.get_child("animations")) {
            auto anim = std::make_shared<nanim::animation>();
            for (auto& pt_frame_child : pt_animation.second.get_child("frames")) {
                auto pt_frame = pt_frame_child.second;
                nanim::frame fram;
                fram.duration_ = pt_frame.get<long>("duration");
                anim->total_duration_ +=  fram.duration_;
                fram.end_time_ = anim->total_duration_;
                float u1 = pt_frame.get<float>("u1");
                float v1 = pt_frame.get<float>("v1");
                float u2 = pt_frame.get<float>("u2");
                float v2 = pt_frame.get<float>("v2");
                fram.image_ = load_texture( (parent_path / pt_frame.get<std::string>("image")).string() );
                int w, h;
                SDL_QueryTexture(fram.image_.get(), NULL, NULL, &w, &h);
                fram.rect_.x = u1 * w;
                fram.rect_.y = v1 * w;
                fram.rect_.w = (u2 - u1) * w;
                fram.rect_.h = (v2 - v1) * h;
                anim->frames_.push_back(fram);
            }
            std::string name = pt_animation.second.get<std::string>("name");
            collec->animations_[name] = anim;
        }
        return collec;
    }

}
