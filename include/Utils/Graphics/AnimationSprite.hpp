#ifndef _SALT2D_UTILS_GRAPHICS_ANIMATIONSPRITE_HPP
#define _SALT2D_UTILS_GRAPHICS_ANIMATIONSPRITE_HPP

#include <chrono>
#include <list>
#include <mutex>

#include <boost/shared_ptr.hpp>

#include <Utils/Graphics/Sprite.hpp>
#include <Utils/Graphics/Texture.hpp>

#include "geometry_defines.hpp"

namespace Utils {

    namespace Graphics {

        /** Спрайт, отображаующий последовательность
          * кадров.
          * @author Elijah Vlasov
        */

        class AnimationSprite: public Sprite {

            public:

                AnimationSprite();
                ~AnimationSprite();

                void addFrame(std::chrono::milliseconds, const boost::shared_ptr<Utils::Graphics::Texture>& frame);

                void onRender(const GeometryDefines::Point& point);
                void onRender(const GeometryDefines::Box& box);
                void onRender(const GeometryDefines::Polygon& polygon);

            private:

                void render();

                struct Frame {

                    std::chrono::milliseconds msDuration;
                    boost::shared_ptr<Utils::Graphics::Texture> texture;

                };

                mutable std::mutex synchroMutex_;

                std::list<Frame> frames_;

                std::chrono::system_clock::time_point lastTimePoint_;

                mutable std::mutex isStartedAccessMutex_;
                bool isStarted_;

                inline bool isStarted() const;

                inline void start();
                inline void stop();

        };



        bool AnimationSprite::isStarted() const {

            std::lock_guard<std::mutex> guard(isStartedAccessMutex_);

            return isStarted_;

        }



        void AnimationSprite::start() {

            std::lock_guard<std::mutex> guard(isStartedAccessMutex_);

            lastTimePoint_ = std::chrono::system_clock::now();

            isStarted_ = true;

        }



        void AnimationSprite::stop() {

            std::lock_guard<std::mutex> guard(isStartedAccessMutex_);

            isStarted_ = false;

        }

    }

}

#endif
