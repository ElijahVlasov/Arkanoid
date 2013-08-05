#ifndef _SALT2D_UTILS_GRAPHICS_GRAPHICSMANAGER_HPP
#define _SALT2D_UTILS_GRAPHICS_GRAPHICSMANAGER_HPP

#include <boost/array.hpp>

#include <Utils/Color.hpp>
#include <Utils/Singleton.hpp>

#include <Utils/Graphics/Texture.hpp>

#include "geometry_defines.hpp"

namespace Utils {

    namespace Graphics {

        /** Класс, инкапсулирующий инициализацию OpenGL
          * и прорисовку текстур.
          * @author Elijah Vlasov
        */

        class GraphicsManager: public Singleton<GraphicsManager> {

            SINGLETON(GraphicsManager)

            private:

                static const Color defaultClearColor_;

            public:

                /** Массив из 4 координат. Используется
                  * для задания координат наложения текстуры
                */

                typedef boost::array<GeometryDefines::Point, 4> CoordArray;

                static const CoordArray UP_COORDS;     /**< Координаты для наложения вверх (обычное наложение).       */
                static const CoordArray DOWN_COORDS;   /**< Координаты для наложения вниз (перевернуто).              */
                static const CoordArray LEFT_COORDS;   /**< Координаты для наложения влево (повернуто на 90 влево).   */
                static const CoordArray RIGHT_COORDS;  /**< Координаты для наложения вправо (повернуто на 90 вправо). */

                /** Отрисовать текстуру в точке.
                */

                static void DrawTexture(const GeometryDefines::Point& point,  const Texture& texture, const CoordArray& texCoords = UP_COORDS);
                static void DrawTexture(const GeometryDefines::PointI& point, const Texture& texture, const CoordArray& texCoords = UP_COORDS);

                /** Отрисовать текстуру в прямоугольнике.
                */

                static void DrawTexture(const GeometryDefines::Box& box,  const Texture& texture, const CoordArray& texCoords = UP_COORDS);
                static void DrawTexture(const GeometryDefines::BoxI& box, const Texture& texture, const CoordArray& texCoords = UP_COORDS);

                static void DrawTexture(const GeometryDefines::Polygon& polygon,  const Texture& texture, const CoordArray& texCoords = UP_COORDS);
                static void DrawTexture(const GeometryDefines::PolygonI& polygon, const Texture& texture, const CoordArray& texCoords = UP_COORDS);

                /** Очистка экрана заданным цветом.
                */

                static void ClearScreen(const Color& clearColor = defaultClearColor_);

                /** Установить размер окна просмотра
                */

                void setViewportSize(unsigned int width, unsigned int height);

            protected:

                GraphicsManager();

            private:

                static float scrWidth_, scrHeight_;

        };

    }

}

#endif
