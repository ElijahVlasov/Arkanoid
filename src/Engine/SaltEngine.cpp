#include <list>
#include <mutex>
#include <thread>

#include <boost/foreach.hpp>
#include <boost/geometry.hpp>
#include <boost/mem_fn.hpp>
#include <boost/shared_ptr.hpp>

#include <Engine/LocationLayer.hpp>
#include <Engine/SaltEngine.hpp>
#include <Engine/World.hpp>

#include <Utils/Lua.hpp>

#include "geometry_defines.hpp"

using namespace std;

using namespace Engine;

using Utils::Lua;



const float SaltEngine::COLLISION_RADIUS = 5.0f;



SaltEngine::SaltEngine(const WorldPtr& world):
    world_(world),
    lua_(Lua::getInstance())
{}



SaltEngine::~SaltEngine() {

    stop();

}



void SaltEngine::run() {

    if(isRunning()) {
        return;
    }

    isRunning_ = true;

    engineThread_ = boost::shared_ptr<std::thread>(new std::thread(boost::mem_fn(&SaltEngine::engineLoop), this) );

    engineThread_->detach();

}



void SaltEngine::stop() {

    std::lock_guard<std::mutex> guard(isRunningAccessMutex_);

    isRunning_ = false;

}



void SaltEngine::engineLoop() {

    while(isRunning()) {

        list<ObjectPtr> objectsForUpdate = getActiveObjects();

        BOOST_FOREACH(ObjectPtr obj, objectsForUpdate) {

            list<ObjectPtr> nearObjects;

        }

    }

}



list<ObjectPtr> SaltEngine::getActiveObjects() {

	list<ObjectPtr> activeObjects;


	return activeObjects;

}



bool SaltEngine::isCollision(const ObjectPtr& obj1, const ObjectPtr& obj2) {

	GeometryDefines::Point obj1Center = obj1->getCenter();
	GeometryDefines::Point obj2Center = obj2->getCenter();

	float dist = boost::geometry::distance(obj1Center, obj2Center);

	if(dist <= COLLISION_RADIUS) {

		return true;

	}

	return false;

}



std::list<ObjectPtr> SaltEngine::getNearObjects(const ObjectPtr& obj) {

	/*

	GeometryDefines::Point areaMinCorner(obj->getPolygon() - COLLISION_RADIUS, obj->box().min_corner().y() - COLLISION_RADIUS);
	GeometryDefines::Point areaMaxCorner(obj->box().max_corner().x() + COLLISION_RADIUS, obj->box().max_corner().y() + COLLISION_RADIUS);

	GeometryDefines::Box objectArea(areaMinCorner, areaMaxCorner);

	LocationLayerPtr objectLayer = obj->getParentLayer();*/

	//return objectLayer->getObjectsInArea(GeometryDefines::Polygon());

	return std::list<ObjectPtr>();

}
