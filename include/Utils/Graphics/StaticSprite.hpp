#ifndef _SALT2D_UTILS_GRAPHICS_STATICSPRITE_HPP
#define _SALT2D_UTILS_GRAPHICS_STATICSPRITE_HPP

#include <boost/shared_ptr.hpp>

#include <Utils/Graphics/GraphicsManager.hpp>
#include <Utils/Graphics/Sprite.hpp>
#include <Utils/Graphics/Texture.hpp>

#include "geometry_defines.hpp"

namespace Utils {

    namespace Graphics {

        /** Спрайт, отображающий только одну текстуру.
          * @author Elijah Vlasov
        */

        class StaticSprite: public Sprite {

            public:

                StaticSprite();
                StaticSprite(const boost::shared_ptr<Texture>& texture);

                ~StaticSprite();

                void onRender(const GeometryDefines::Point& point);
                void onRender(const GeometryDefines::Box&   box);
                void onRender(const GeometryDefines::Polygon& polygon);

                /** Получить текстуру.
                */

                boost::shared_ptr<Texture> getTexture() const;

                /** Установить текстуру.
                */

                void setTexture(const boost::shared_ptr<Texture>& texture);

            private:

                boost::shared_ptr<Texture> texture_;

        };

    }

}

#endif
