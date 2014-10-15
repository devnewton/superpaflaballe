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
        if (TTF_Init() != 0) {
            throw sdl_exception();
        }
        const int img_flags = IMG_INIT_PNG;
        int img_initted = IMG_Init(img_flags);
        if ((img_initted & img_flags) != img_flags) {
            throw sdl_exception();
        }
        int mix_flags = MIX_INIT_OGG;
        int mix_initted = Mix_Init(mix_flags);
        if ((mix_initted & mix_flags) != mix_flags) {
            throw sdl_exception();
        }
       if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT , 2, 1024) != 0 ) {
            throw sdl_exception();
        }
    }

    assets::~assets() {
        Mix_CloseAudio();
        Mix_Quit();
        IMG_Quit();
        TTF_Quit();
    }

    std::shared_ptr< TTF_Font > assets::font(const std::string& path, int size) {
        auto key = std::make_pair(path, size);
        auto font = fonts_[key].lock();
        if (font) {
            return font;
        }
        boost::filesystem::path fspath(path);
        for (auto& prefix : pathPrefixes_) {
            boost::filesystem::path fsprefix(prefix);
            font = load_font((fsprefix / fspath).string(), size);
            if (font) {
                fonts_[key] = font;
                return font;
            }
        }
        throw std::runtime_error("Cannot load font " + path);
    }

    std::shared_ptr< TTF_Font > assets::load_font(const std::string path, int size) {
        return std::shared_ptr< TTF_Font >(TTF_OpenFont(path.c_str(), size), TTF_CloseFont);
    }

    std::shared_ptr< Mix_Music > assets::music(const std::string& path) {
        auto music = musics_[path].lock();
        if (music) {
            return music;
        }
        boost::filesystem::path fspath(path);
        for (auto& prefix : pathPrefixes_) {
            boost::filesystem::path fsprefix(prefix);
            music = load_music((fsprefix / fspath).string());
            if (music) {
                musics_[path] = music;
                return music;
            }
        }
        throw std::runtime_error("Cannot load music " + path);
    }

     std::shared_ptr< Mix_Music > assets::load_music(const std::string& path) {
        return std::shared_ptr< Mix_Music >(Mix_LoadMUS(path.c_str()), Mix_FreeMusic);
    }

    std::shared_ptr< SDL_Texture > assets::texture(const std::string& path) {
        auto texture = textures_[path].lock();
        if (texture) {
            return texture;
        }
        boost::filesystem::path fspath(path);
        for (auto& prefix : pathPrefixes_) {
            boost::filesystem::path fsprefix(prefix);
            texture = load_texture((fsprefix / fspath).string());
            if (texture) {
                textures_[path] = texture;
                return texture;
            }
        }
        throw std::runtime_error("Cannot load texture " + path);
    }

    std::shared_ptr< SDL_Texture > assets::load_texture(const std::string path) {
        return std::shared_ptr< SDL_Texture >(IMG_LoadTexture(game_.renderer(), path.c_str()), SDL_DestroyTexture);
    }

    std::shared_ptr< nanim::collection > assets::animations(const std::string& path) {
        auto animations = animations_[path].lock();
        if (animations) {
            return animations;
        }
        for (auto& prefix : pathPrefixes_) {
            try {
                animations = load_json_nanim(prefix + path);
                if (animations) {
                    animations_[path] = animations;
                    return animations;
                }
            } catch (...) {
            }
        }
        throw std::runtime_error("Cannot load animations " + path);
    }

    std::shared_ptr<nanim::collection> assets::load_json_nanim(const std::string& path) {
        using boost::property_tree::ptree;
        if (!boost::filesystem::exists(path)) {
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
                anim->total_duration_ += fram.duration_;
                fram.end_time_ = anim->total_duration_;
                float u1 = pt_frame.get<float>("u1");
                float v1 = pt_frame.get<float>("v1");
                float u2 = pt_frame.get<float>("u2");
                float v2 = pt_frame.get<float>("v2");
                fram.image_ = load_texture((parent_path / pt_frame.get<std::string>("image")).string());
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
