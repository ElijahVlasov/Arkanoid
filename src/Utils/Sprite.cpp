#include <Utils/Sprite.hpp>

#include "geometry_defines.hpp"

using namespace Utils;



Sprite::~Sprite() {}



void Sprite::onRender(const GeometryDefines::PointI& point) {

    onRender(GeometryDefines::PointIToPoint(point));

}



void Sprite::onRender(const GeometryDefines::BoxI box) {

    onRender(GeometryDefines::BoxIToBox(box));

}



void Sprite::onRender(const GeometryDefines::PolygonI polygon) {

    onRender(GeometryDefines::PolygonIToPolygon(polygon));

}
