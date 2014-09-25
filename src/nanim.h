#ifndef nanim_h
#define	nanim_h

#include <SDL.h>
#include <memory>
#include <map>
#include <vector>

namespace superpaflaballe {
    class assets;

    namespace nanim {

        class collection;
        class animation;
        class play;

        class frame {
        public:
            long duration() const;
            std::shared_ptr<SDL_Texture> image() const;
            const SDL_Rect& rect() const;
        private:
            long duration_;
            std::shared_ptr<SDL_Texture> image_;
            SDL_Rect rect_;
            long end_time_;

            friend class ::superpaflaballe::assets;
            friend class play;
        };

        enum play_mode {
            once,
            loop
        };

        class play {
        public:
            play(std::shared_ptr<animation> a, play_mode m);
            void start(play_mode m);
            void stop();
            bool is_stopped() const;
            play_mode mode() const;
            void update(long elapsed_time);
            const frame& current_frame() const;
        private:

            enum state {
                started,
                stopped
            };
            std::shared_ptr<animation> animation_;
            int current_frame_index_;
            long current_time;
            play_mode mode_;
            state state_;
        };

        class animation {

        private:
            std::vector<frame> frames_;
            long total_duration_;

            friend class ::superpaflaballe::assets;
            friend class play;
        };

        class collection {
        public:
            std::shared_ptr<animation> get(const std::string& name);
            std::shared_ptr<animation> first();

        private:
            std::map< std::string, std::shared_ptr<animation> > animations_;

            friend class ::superpaflaballe::assets;
        };
    }

}

#endif

