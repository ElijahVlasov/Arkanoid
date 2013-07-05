#include <cmath>

#include <list>
#include <mutex>
#include <stdexcept>
#include <string>

#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <Engine/Direction.hpp>
#include <Engine/Object.hpp>
#include <Engine/Renderer.hpp>

#include <Utils/ResourceManager.hpp>

#include "geometry_defines.hpp"

using namespace std;

using namespace Engine;

using namespace Utils;



Object::Object():
    sprite_(reinterpret_cast<ISprite*>(0)),
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



void Object::move(float step) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    GeometryDefines::Point movementVector(cos(direction_) * step, sin(direction_) * step);

    GeometryDefines::Polygon::ring_type& polygonPoints = polygon_.outer();

    BOOST_FOREACH(GeometryDefines::Point& polygonPoint, polygonPoints) {

    	float newX = polygonPoint.x() + movementVector.x();
    	float newY = polygonPoint.y() + movementVector.y();

    	polygonPoint.x(newX);
    	polygonPoint.y(newY);

    }

}



void Object::spin(float step) {

	std::lock_guard<std::mutex> guard(synchroMutex_);

	GeometryDefines::Polygon::ring_type& polygonPoints = polygon_.outer();

	addToDirection(step);

	BOOST_FOREACH(GeometryDefines::Point& polygonPoint, polygonPoints) {

		float angle = step * (2 * PI);

		float newX = polygonPoint.x() * cos(angle) - polygonPoint.y() * sin(angle);
		float newY = polygonPoint.x() * sin(angle) + polygonPoint.y() * cos(angle);

		polygonPoint.x(newX);
		polygonPoint.y(newY);

	}

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



float Object::getDirection() const {

    return direction_;

}



Object::DirectionVector Object::getDirectionVector() const {

    return Object::DirectionVector(cos(direction_), sin(direction_));

}



GeometryDefines::Polygon Object::getPolygon() const {

	std::lock_guard<std::mutex> guard(synchroMutex_);

    return polygon_;

}



GeometryDefines::Point Object::getCenter() const {

	std::lock_guard<std::mutex> guard(synchroMutex_);

	GeometryDefines::Point center;

	boost::geometry::centroid(polygon_, center);

	return center;

}
