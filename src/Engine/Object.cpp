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

using namespace Engine;

using namespace Utils;

using namespace boost::geometry::model;
using namespace boost::geometry::model::d2;



Object::Object():
    renderer_(reinterpret_cast<IRenderer*>(0))
{}



Object::~Object() {}



int Object::getId() const {

    return id_;

}



void Object::onRender() {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    if(renderer_ != 0) {
        renderer_->onRender();
    }

}



void Object::move(float xShift, float yShift) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    Point& min = box_.min_corner();
    Point& max = box_.max_corner();

    Polygon wayPolygon;

    // Составляем многоугольник для пути
    Polygon::ring_type& wayOuter = wayPolygon.outer();

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



void Object::setRenderer(const boost::shared_ptr<IRenderer>& renderer) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    renderer_ = renderer;

}



Box& Object::box() {

    return box_;

}
