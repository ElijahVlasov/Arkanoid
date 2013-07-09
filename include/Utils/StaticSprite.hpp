#ifndef _SALT2D_UTILS_STATICSPRITE_HPP
#define _SALT2D_UTILS_STATICSPRITE_HPP

#include <boost/shared_ptr.hpp>

#include <Utils/Graphics.hpp>
#include <Utils/Sprite.hpp>
#include <Utils/Texture.hpp>

#include "geometry_defines.hpp"

namespace Utils {

    class StaticSprite: public Sprite {

        public:

            StaticSprite();
            StaticSprite(const boost::shared_ptr<Utils::Texture>& texture);

            ~StaticSprite();

            void onRender(const GeometryDefines::Point& point);
            void onRender(const GeometryDefines::Box&   box);
            void onRender(const GeometryDefines::Polygon& polygon);

            boost::shared_ptr<Utils::Texture> getTexture() const;
            void setTexture(const boost::shared_ptr<Utils::Texture>& texture);

        private:

            boost::shared_ptr<Utils::Texture> texture_;

    };

}

#endif
