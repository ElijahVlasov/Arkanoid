#ifndef _SALT2D_UTILS_GRAPHICS_HPP
#define _SALT2D_UTILS_GRAPHICS_HPP

#include <boost/array.hpp>

#include <boost/geometry/geometries/point_xy.hpp>

#include <Utils/Singleton.hpp>
#include <Utils/Texture.hpp>

namespace Utils {

    class Graphics: public Singleton<Graphics> {

        SINGLETON(Graphics)

        public:

            typedef boost::array<boost::geometry::model::d2::point_xy<float>, 4> CoordArray; 

            static void DrawTexture(float x, float y, const Texture& texture);
            static void DrawTexture(float x, float y, float width, float height, const Texture& texture);
            static void DrawTexture(float x, float y, float width, float height, const CoordArray& texCoords, const Texture& texture);

            void setViewportSize(unsigned int width, unsigned int height);

        protected:

            Graphics();      

    };

}

#endif
