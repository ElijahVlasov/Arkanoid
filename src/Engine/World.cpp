#include <list>
#include <stdexcept>
#include <string>

#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include <Engine/Location.hpp>
#include <Engine/World.hpp>

#include <Utils/LocalizationManager.hpp>
#include <Utils/Lua.hpp>
#include <Utils/ResourceManager.hpp>
#include <Utils/SingletonPointer.hpp>

#include "Resource.pb.h"
#include "World.pb.h"

using namespace std;

using namespace Engine;

using namespace Utils;



World::World() {

    try {

        resourceManager_ = ResourceManager::getInstance();

    } catch (const runtime_error&) {}

}



World::World(const EngineData::World& worldData) throw(runtime_error):
    resourceManager_(ResourceManager::getInstance())
{

    SingletonPointer<LocalizationManager> localizationManager = LocalizationManager::getInstance();
    SingletonPointer<Lua> lua = Lua::getInstance();

    name_ = localizationManager->getString(worldData.name());
    desc_ = localizationManager->getString(worldData.desc());

    auto locations = worldData.location();

    BOOST_FOREACH(EngineData::Location locationData, locations) {

        LocationPtr newLocation(new Location(locationData));

        if(locationData.has_on_create()) {

            luabind::object onCreate = lua->getFunctionObject(locationData.on_create());

            try {

                luabind::call_function<void>(onCreate, newLocation);

            } catch(const luabind::error& err) {

                throw(runtime_error(err.what()));

            }

        }

        locations_.push_back(newLocation);

    }

    auto resources = worldData.resources();

    BOOST_FOREACH(EngineData::Resource resource, resources) {

        resources_.push_back( resourceManager_->getResource( static_cast<ResourceManager::ResourceType>(resource.type()), resource.resource_name() ) );

    }

}



World::~World() {

    BOOST_FOREACH(boost::shared_ptr<Resource> resource, resources_) {

        resourceManager_->deleteResource(resource);

    }

}



void World::setName(const char* name) {

    if(name == 0) {
        name_ = "";
    } else {
        name_ = name;
    }

}



void World::setName(const string& name) {

    name_ = name;

}



const string& World::getName() const {

    return name_;

}



void World::setDescription(const char* desc) {

    if(desc == 0) {
        desc_ = "";
    } else {
        desc_ = desc;
    }

}



void World::setDescription(const string& desc) {

    desc_ = desc;

}



const string& World::getDescription() const {

    return desc_;

}



void World::addLocation(const LocationPtr& location) {

    locations_.push_back(location);

}



const list<LocationPtr>& World::getLocations() const {

    return locations_;

}
