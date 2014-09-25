#ifndef superpaflaballe_assets_h
#define superpaflaballe_assets_h

#include "game.h"
#include "nanim.h"

namespace superpaflaballe {

    class assets {
    public:
        assets(game& game);
        ~assets();

        std::shared_ptr< SDL_Texture > texture(const std::string& path);
        std::shared_ptr< nanim::collection > animations(const std::string& path);

    private:
        std::shared_ptr<nanim::collection> load_json_nanim(const std::string& path);
        std::shared_ptr< SDL_Texture > load_texture(const std::string path);

        game& game_;
        std::vector<std::string> pathPrefixes_;

    };

}

#endif