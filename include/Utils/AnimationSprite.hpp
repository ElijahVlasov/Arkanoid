#ifndef _SALT2D_UTILS_ANIMATIONSPRITE_HPP
#define _SALT2D_UTILS_ANIMATIONSPRITE_HPP

#include <chrono>
#include <list>

#include <boost/shared_ptr.hpp>

#include <Utils/ISprite.hpp>
#include <Utils/Texture.hpp>

#include "geometry_defines.hpp"

namespace Utils {

    class AnimationSprite: public ISprite {

        public:

            AnimationSprite();
            ~AnimationSprite();

            void addFrame(std::chrono::milliseconds, const boost::shared_ptr<Utils::Texture>& frame);

            void onRender(const GeometryDefines::Point& point);
            void onRender(const GeometryDefines::Box& box);
            void onRender(const GeometryDefines::Polygon& polygon);

        private:

            struct Frame {

                std::chrono::milliseconds msDuration;
                boost::shared_ptr<Utils::Texture> texture;

            };

            std::list<Frame> frames_;

            bool isStarted_;

    };

}

#endif
