#include <cmath>

#include <list>
#include <mutex>
#include <stdexcept>
#include <string>

#include <boost/foreach.hpp>
#include <boost/geometry.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <Engine/Location.hpp>
#include <Engine/Object.hpp>
#include <Engine/Renderer.hpp>

#include <Utils/ResourceManager.hpp>

#include <Utils/Graphics/Sprite.hpp>

#include "geometry_defines.hpp"

using namespace std;

using namespace Engine;

using namespace Utils;
using namespace Utils::Graphics;



Object::Object():
    sprite_(reinterpret_cast<Sprite*>(0)),
    id_(boost::uuids::random_generator()())
{}



Object::~Object() {}



boost::uuids::uuid Object::getId() const {

    return id_;

}



void Object::onRender() {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    if(sprite_ != 0) {
        sprite_->onRender(polygon_);
    }

}



void Object::setLocation(const LocationPtr& location) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    location_ = location;

}



const LocationPtr& Object::getLocation() const {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    return location_;

}



void Object::setSprite(const boost::shared_ptr<Sprite>& sprite) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    sprite_ = sprite;

}



float Object::getDirection() const {

    return direction_;

}



Object::DirectionVector Object::getDirectionVector() const {

    float radianDirection = direction_ * 2 * PI;

    return Object::DirectionVector(cos(radianDirection), sin(radianDirection));

}



GeometryDefines::Polygon Object::getPolygon() const {

	std::lock_guard<std::mutex> guard(synchroMutex_);

    return polygon_;

}



GeometryDefines::Polygon& Object::polygon() {

    return polygon_;

}



GeometryDefines::Point Object::getCenter() const {

	std::lock_guard<std::mutex> guard(synchroMutex_);

	GeometryDefines::Point center;

	boost::geometry::centroid(polygon_, center);

	return center;

}
