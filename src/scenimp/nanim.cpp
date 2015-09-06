#include "nanim.h"

namespace scenimp {
    namespace nanim {

        long frame::duration() const {
            return duration_;
        }

        std::shared_ptr<SDL_Texture> frame::image() const {
            return image_;
        }

        const SDL_Rect& frame::rect() const {
            return rect_;
        }

        play::play(std::shared_ptr<animation> a, play_mode m)
        : animation_(a) {
            start(m);
        }

        void play::start(play_mode m) {
            state_ = started;
            current_time = 0;
            current_frame_index_ = 0;
            mode_ = m;
        }

        void play::stop() {
            state_ = stopped;
            current_time = 0;
            current_frame_index_ = 0;
        }

        bool play::is_stopped() const {
            return state_ == stopped;
        }

        play_mode play::mode() const {
            return mode_;
        }

        void play::update(long elapsed_time) {
            if (state_ == stopped) {
                return;
            }
            current_time += elapsed_time;
            if (current_time >= animation_->total_duration_) {
                switch (mode_) {
                    case once:
                        current_frame_index_ = animation_->frames_.size() - 1;
                        state_ = stopped;
                        return;
                    case loop:
                        current_time %= animation_->total_duration_;
                        current_frame_index_ = 0;
                        break;
                }
            }
            while (current_time > animation_->frames_[current_frame_index_].end_time_) {
                ++current_frame_index_;
            }
        }

        const frame& play::current_frame() const {
            return animation_->frames_[current_frame_index_];
        }

        std::shared_ptr<::scenimp::nanim::play> animation::play(play_mode m) {
            return std::make_shared<::scenimp::nanim::play>(shared_from_this(), m);
        }

        std::shared_ptr<animation> collection::get(const std::string& name) {
            return animations_[name];
        }

        std::shared_ptr<animation> collection::first() {
            return animations_.begin()->second;
        }
        
        std::shared_ptr<::scenimp::nanim::play> collection::play(play_mode m) {
            return first()->play(m);
        }
    }
}
