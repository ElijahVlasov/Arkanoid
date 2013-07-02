#ifndef _SALT2D_ENGINE_ANIMATIONSPRITE_HPP
#define _SALT2D_ENGINE_ANIMATIONSPRITE_HPP

#include <list>

#include <boost/shared_ptr.hpp>

#include <Engine/Direction.hpp>
#include <Engine/ISprite.hpp>

#include <Utils/Texture.hpp>

#include "geometry_defines.hpp"

namespace Engine {

    class AnimationSprite: public ISprite {

        public:

            AnimationSprite();
            ~AnimationSprite();

            void addFrame(int msDuration, const boost::shared_ptr<Utils::Texture>& frame);

            void onRender(const GeometryDefines::Point& point);
            void onRender(const GeometryDefines::Box& box);
            void onRender(const GeometryDefines::Polygon& polygon);

        private:

            struct Frame {

                int msDuration;
                boost::shared_ptr<Utils::Texture> texture;

            };

            std::list<Frame> frames_;

            bool isStarted_;

    };

}

#endif
