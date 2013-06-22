#ifndef _SALT2D_ENGINE_STATICSPRITE_HPP
#define _SALT2D_ENGINE_STATICSPRITE_HPP

#include <boost/shared_ptr.hpp>

#include <Engine/Direction.hpp>
#include <Engine/ISprite.hpp>

#include <Utils/Graphics.hpp>
#include <Utils/Texture.hpp>

#include "geometry_defines.hpp"

namespace Engine {

    class StaticSprite: public ISprite {

        public:

            StaticSprite();
            StaticSprite(const boost::shared_ptr<Utils::Texture>& texture);

            void onRender(const GeometryDefines::Point& drawPoint, Direction dir);

            boost::shared_ptr<Utils::Texture> getTexture() const;
            void setTexture(const boost::shared_ptr<Utils::Texture>& texture);

        private:

            boost::shared_ptr<Utils::Texture> texture_;

    };

}

#endif
