#ifndef _SALT2D_ENGINE_OBJECT_HPP
#define _SALT2D_ENGINE_OBJECT_HPP

#include <boost/shared_ptr.hpp>

#include <Utils/Graphics/Sprite.hpp>

#include "geometry_defines.hpp"

namespace Engine {

    class Object {

        public:

            virtual ~Object();

            virtual void draw();

            void setSprite(const boost::shared_ptr<Utils::Graphics::Sprite>& sprite);
            const boost::shared_ptr<Utils::Graphics::Sprite>& getSprite() const;

            virtual GeometryDefines::Box getRect() const = 0;

        private:

            boost::shared_ptr<Utils::Graphics::Sprite> sprite_;

    };

}

#endif
