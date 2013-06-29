#include <list>
#include <mutex>
#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <Engine/Direction.hpp>
#include <Engine/Object.hpp>
#include <Engine/Renderer.hpp>

#include <Utils/ResourceManager.hpp>

#include "geometry_defines.hpp"

using namespace std;

using namespace GeometryDefines;

using namespace Engine;

using namespace Utils;



Object::Object():
    sprite_(reinterpret_cast<ISprite*>(0))
{}



Object::~Object() {}



int Object::getId() const {

    return id_;

}



void Object::onRender() {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    if(sprite_ != 0) {
        sprite_->onRender(box_, dir_);
    }

}



void Object::move(float xShift, float yShift) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    Point& min = box_.min_corner();
    Point& max = box_.max_corner();

    GeometryDefines::Polygon wayPolygon;

    // Составляем многоугольник для пути
    GeometryDefines::Polygon::ring_type& wayOuter = wayPolygon.outer();

    // верхняя левая точка объекта
    wayOuter.push_back(Point(min.x(),             max.y()         ));
    // верхняя левая точка объекта в новом положении
    wayOuter.push_back(Point(min.x() + xShift,    max.y() + yShift));
    // верхняя правая точка объекта в новом положении
    wayOuter.push_back(Point(max.x() + xShift,    max.y() + yShift));
    // правая нижняя точка объекта в новом положении
    wayOuter.push_back(Point(max.x() + xShift,    min.y() + yShift));
    // правая нижняя точка объекта
    wayOuter.push_back(Point(max.x(),             min.y()         ));
    // правая верхняя точка объекта
    wayOuter.push_back(Point(max.x(),             max.y()         ));

    list<ObjectPtr> objectsOnWay = parentLayer_->getObjectsInArea(wayPolygon);

    if((objectsOnWay.empty())
        || ( (objectsOnWay.size() == 1) && (*objectsOnWay.front() == *this) )) { // если путь пустой

        min.x(min.x() + xShift);
        max.x(max.x() + xShift);

        min.y(min.y() + yShift);
        max.y(max.y() + yShift);

        return;

    }

    // есть потенциальные объекты для столкновений

}



void Object::setDirection(Direction dir) {

    dir_ = dir;

}



Direction Object::getDirection() const {

    return dir_;

}



void Object::setParentLayer(const LocationLayerPtr& layer) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    parentLayer_ = layer;

}



const LocationLayerPtr& Object::getParentLayer() const {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    return parentLayer_;

}



void Object::setSprite(const boost::shared_ptr<ISprite>& sprite) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    sprite_ = sprite;

}



Box& Object::box() {

    return box_;

}



GeometryDefines::Point Object::getCenter() const {

	float minCornerX = box_.min_corner().x();
	float maxCornerX = box_.max_corner().x();
	float minCornerY = box_.min_corner().y();
	float maxCornerY = box_.max_corner().y();

	float centerX = (minCornerX + maxCornerX) / 2; // равносильно centerX = minCornerX + (maxCornerX - minCornerX) / 2;
	float centerY = (minCornerY + maxCornerY) / 2;

	return Point(centerX, centerY);

}
