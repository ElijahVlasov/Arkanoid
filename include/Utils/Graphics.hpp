#ifndef _SALT2D_UTILS_GRAPHICS_HPP
#define _SALT2D_UTILS_GRAPHICS_HPP

#include <boost/array.hpp>

#include <Utils/Color.hpp>
#include <Utils/Singleton.hpp>
#include <Utils/Texture.hpp>

#include "geometry_defines.hpp"

namespace Utils {

    /** Класс, инкапсулирующий инициализацию OpenGL
      * и прорисовку текстур.
      * @author Elijah Vlasov
    */

    class Graphics: public Singleton<Graphics> {

        SINGLETON(Graphics)

        private:

            static const Color defaultClearColor_;

        public:

            /** Массив из 4 координат. Используется
              * для задания координат наложения текстуры
            */

            typedef boost::array<GeometryDefines::Point, 4> CoordArray;

            static const CoordArray UP_COORDS;
            static const CoordArray DOWN_COORDS;
            static const CoordArray LEFT_COORDS;
            static const CoordArray RIGHT_COORDS;

            static void DrawTexture(const GeometryDefines::Point& point, const Texture& texture,  const CoordArray& texCoords = UP_COORDS);
            static void DrawTexture(const GeometryDefines::PointI& point, const Texture& texture, const CoordArray& texCoords = UP_COORDS);

            static void DrawTexture(const GeometryDefines::Box& box, const Texture& texture,  const CoordArray& texCoords = UP_COORDS);
            static void DrawTexture(const GeometryDefines::BoxI& box, const Texture& texture, const CoordArray& texCoords = UP_COORDS);

            /** Очистка экрана заданным цветом.
            */

            static void ClearScreen(const Color& clearColor = defaultClearColor_);

            /** Установить размер окна просмотра
            */

            void setViewportSize(unsigned int width, unsigned int height);

        protected:

            Graphics();

        private:

            static float scrWidth_, scrHeight_;

    };

}

#endif
