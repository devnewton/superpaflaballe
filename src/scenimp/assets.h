#pragma once

#include "nanim.h"
#include <SDL_mixer.h>
#include <SDL_ttf.h>

namespace scenimp {

    class game;

    class assets {
    public:
        assets(game& game);
        ~assets();

        std::shared_ptr< nanim::collection > animations(const std::string& path);
        std::shared_ptr< TTF_Font > font(const std::string& path, int size);
        std::shared_ptr< Mix_Music > music(const std::string& path);
        std::shared_ptr< SDL_Texture > texture(const std::string& path);


    private:
        std::shared_ptr< TTF_Font > load_font(const std::string path, int size);
        std::shared_ptr<nanim::collection> load_json_nanim(const std::string& path);
        std::shared_ptr< Mix_Music > load_music(const std::string& path);
        std::shared_ptr< SDL_Texture > load_texture(const std::string path);

        game& game_;
        std::vector<std::string> pathPrefixes_;
        std::map<std::string, std::weak_ptr< nanim::collection > > animations_;
        std::map<std::pair<std::string, int/*font size*/>, std::weak_ptr< TTF_Font > > fonts_;
        std::map<std::string, std::weak_ptr< SDL_Texture > > textures_;
        std::map<std::string, std::weak_ptr< Mix_Music > > musics_;
    };

}
