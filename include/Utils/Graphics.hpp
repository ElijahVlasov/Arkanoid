#ifndef _SALT2D_UTILS_GRAPHICS_HPP
#define _SALT2D_UTILS_GRAPHICS_HPP

#include <boost/array.hpp>

#include <boost/geometry/geometries/point_xy.hpp>

#include <Utils/Singleton.hpp>
#include <Utils/Texture.hpp>

namespace Utils {

    /** Класс, инкапсулирующий инициализацию OpenGL
      * и прорисовку текстур.
      * @author Elijah Vlasov
    */

    class Graphics: public Singleton<Graphics> {

        SINGLETON(Graphics)

        public:

            /** Массив из 4 координат. Используется
              * для задания координат наложения текстуры
            */

            typedef boost::array<boost::geometry::model::d2::point_xy<float>, 4> CoordArray; 

            /** Прорисовка текстуры в стандартном виде.
              * @param x координата на экране для прорисовки
              * @param y координата на экране для прорисовки
              * @param texture текстура для прорисовки
            */

            static void DrawTexture(float x, float y, const Texture& texture);

            /** Прорисовка текстуры в прямоугольнике width * height.
              * @param x координата на экране для прорисовки
              * @param y координата на экране для прорисовки
              * @param widht ширина
              * @param height высота
              * @param texture текстура для прорисовки
            */

            static void DrawTexture(float x, float y, float width, float height, const Texture& texture);

            /** Прорисовка текстуры в прямоугольнике width * height с координатами наложения.
              * @param x координата на экране для прорисовки
              * @param y координата на экране для прорисовки
              * @param widht ширина
              * @param height высота
              * @param texCoords координаты наложения
              * @param texture текстура для прорисовки
            */

            static void DrawTexture(float x, float y, float width, float height, const CoordArray& texCoords, const Texture& texture);

            /** Установить размер окна просмотра
            */

            void setViewportSize(unsigned int width, unsigned int height);

        protected:

            Graphics();      

    };

}

#endif
