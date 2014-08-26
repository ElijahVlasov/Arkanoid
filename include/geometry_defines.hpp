#ifndef _SALT2D_GEOMERTY_DEFINES_HPP
#define _SALT2D_GEOMERTY_DEFINES_HPP

#include <cmath>

#include <boost/foreach.hpp>

#include <boost/geometry.hpp>
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

    inline bool boxAndCircleContact(float radius, const Point& center, const Box& box, Point& contact);

    typedef Point Vector2D;
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



bool GeometryDefines::boxAndCircleContact(float radius, const GeometryDefines::Point& center, const GeometryDefines::Box& box, GeometryDefines::Point& contact) {

    if(center.y() > box.max_corner().y()) { // Сверху

        if(center.x() < box.min_corner().x()) { // Слева

            GeometryDefines::Point leftTopCorner(box.min_corner().x(), box.max_corner().y());

            if(boost::geometry::distance(center, leftTopCorner) <= radius) {

                contact = leftTopCorner;

                return true;

            }

        } else if(center.x() > box.max_corner().x()) { // Справа

            if(boost::geometry::distance(center, box.max_corner()) <= radius) {

                contact = box.max_corner();

                return true;

            }

        } else { // Посередине

            if(abs(center.y() - box.max_corner().y()) <= radius) {

                contact.x(center.x());
                contact.y(box.max_corner().y());

                return true;

            }

        }

    } else if(center.y() < box.min_corner().y()) { // Снизу

        if(center.x() < box.min_corner().x()) { // Слева

            if(boost::geometry::distance(center, box.min_corner()) <= radius) {

                contact = box.min_corner();

                return true;

            }

        } else if(center.x() > box.max_corner().x()) { // Справа

            GeometryDefines::Point rightBottomCorner(box.max_corner().x(), box.min_corner().y());

            if(boost::geometry::distance(center, rightBottomCorner) <= radius) {

                contact = rightBottomCorner;

                return true;

            }

        } else { // Посередине

            if(abs(center.y() - box.min_corner().y()) <= radius) {

                contact.x(center.x());
                contact.y(box.min_corner().y());

                return true;

            }

        }

    } else { // Посередине


        if(center.x() < box.min_corner().x()) {

            if(abs(box.min_corner().x() - center.x()) <= radius) {

                contact.x(box.min_corner().x());
                contact.y(center.y());

                return true;

            }

        } else {

            if(abs(box.max_corner().x() - center.x()) <= radius) {

                contact.x(box.max_corner().x());
                contact.y(center.y());

                return true;

            }

        }

    }

    return false;

}

#endif
