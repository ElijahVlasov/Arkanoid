#include <mutex>
#include <stdexcept>
#include <string>

#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/geometries/point_xy.hpp>

#include <boost/shared_ptr.hpp>

#include <Engine/Direction.hpp>
#include <Engine/Object.hpp>
#include <Engine/Renderer.hpp>

#include <Utils/ResourceManager.hpp>

using namespace std;

using namespace Engine;

using namespace Utils;

using namespace boost::geometry::model;



Object::Object():
    renderer_((IRenderer*)0)
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

    d2::point_xy<float>& min = box_.min_corner();
    d2::point_xy<float>& max = box_.max_corner();

    min.x(min.x() + xShift);
    max.x(max.x() + xShift);

    min.y(min.y() + yShift);
    max.y(max.y() + yShift);
    
}



void Object::setDirection(DIRECTION dir) {
    
    dir_ = dir;
    
}



DIRECTION Object::getDirection() const {

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



box< d2::point_xy<float> >& Object::box() {

    return box_;

}
