#include <list>
#include <thread>

#include <boost/foreach.hpp>
#include <boost/geometry.hpp>
#include <boost/mem_fn.hpp>
#include <boost/shared_ptr.hpp>

#include <Engine/LocationLayer.hpp>
#include <Engine/SaltEngine.hpp>

#include <Utils/Lua.hpp>

#include "geometry_defines.hpp"

using namespace std;

using namespace Engine;

using Utils::Lua;



const float SaltEngine::COLLISION_RADIUS = 5.0f;



SaltEngine::SaltEngine():
    lua_(Lua::getInstance(), false)
{}



SaltEngine::~SaltEngine() {}



void SaltEngine::run() {

    engineThread_ = boost::shared_ptr<std::thread>(new std::thread(boost::mem_fn(&SaltEngine::engineLoop), this) );

}



void SaltEngine::engineLoop() {

    list<ObjectPtr> objectsForUpdate = getActiveObjects();

    BOOST_FOREACH(ObjectPtr obj, objectsForUpdate) {

    	list<ObjectPtr> nearObjects;

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

	GeometryDefines::Point areaMinCorner(obj->box().min_corner().x() - COLLISION_RADIUS, obj->box().min_corner().y() - COLLISION_RADIUS);
	GeometryDefines::Point areaMaxCorner(obj->box().max_corner().x() + COLLISION_RADIUS, obj->box().max_corner().y() + COLLISION_RADIUS);

	GeometryDefines::Box objectArea(areaMinCorner, areaMaxCorner);

	LocationLayerPtr objectLayer = obj->getParentLayer();

	return objectLayer->getObjectsInArea(objectArea);

}
