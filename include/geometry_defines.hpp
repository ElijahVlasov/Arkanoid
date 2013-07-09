#ifndef _SALT2D_GEOMERTY_DEFINES_HPP
#define _SALT2D_GEOMERTY_DEFINES_HPP

#include <boost/foreach.hpp>

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#define PI 3.141592f

namespace GeometryDefines {

    typedef boost::geometry::model::d2::point_xy<int>   PointI;
    typedef boost::geometry::model::box<PointI>         BoxI;
    typedef boost::geometry::model::polygon<PointI>     PolygonI;

    typedef boost::geometry::model::d2::point_xy<float> Point;
    typedef boost::geometry::model::box<Point>          Box;
    typedef boost::geometry::model::polygon<Point>      Polygon;

    inline Point PointIToPoint(const PointI&);
    inline Box BoxIToBox(const BoxI&);
    inline Polygon PolygonIToPolygon(const PolygonI&);

}



GeometryDefines::Point GeometryDefines::PointIToPoint(const GeometryDefines::PointI& point) {

    return GeometryDefines::Point(static_cast<float>(point.x()), static_cast<float>(point.y()));

}



GeometryDefines::Box GeometryDefines::BoxIToBox(const GeometryDefines::BoxI& box) {

    return GeometryDefines::Box(GeometryDefines::PointIToPoint(box.min_corner()), GeometryDefines::PointIToPoint(box.max_corner()));

}



GeometryDefines::Polygon GeometryDefines::PolygonIToPolygon(const GeometryDefines::PolygonI& polygon) {

    GeometryDefines::Polygon res;
    GeometryDefines::Polygon::ring_type& resOuter = res.outer();

    BOOST_FOREACH(GeometryDefines::PointI point, polygon.outer()) {

        resOuter.push_back(GeometryDefines::PointIToPoint(point));

    }

    return res;

}

#endif
