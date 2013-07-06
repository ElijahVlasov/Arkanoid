#include <list>
#include <stdexcept>
#include <string>

#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>

#include <Engine/Location.hpp>
#include <Engine/World.hpp>

#include <Utils/LocalizationManager.hpp>
#include <Utils/SingletonPointer.hpp>

#include "World.pb.h"

using namespace std;

using namespace Engine;

using namespace Utils;



World::World() {}



World::World(const EngineData::World& worldData) {

    try {

        SingletonPointer<LocalizationManager> localizationManager = LocalizationManager::getInstance();

        name_ = localizationManager->getString(worldData.name());
        desc_ = localizationManager->getString(worldData.desc());

    } catch(const std::runtime_error&) {}

    auto locations = worldData.location();

    BOOST_FOREACH(EngineData::Location locationData, locations) {

        locations_.push_back(LocationPtr(new Location(locationData)));

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
