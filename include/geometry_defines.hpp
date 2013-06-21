#ifndef _SALT2D_GEOMERTY_DEFINES_HPP
#define _SALT2D_GEOMERTY_DEFINES_HPP

#include <boost/geometry.hpp>

typedef boost::geometry::model::d2::point_xy<float> Point;
typedef boost::geometry::model::box<Point>          Box;
typedef boost::geometry::model::polygon<Point>      Polygon;

#endif
