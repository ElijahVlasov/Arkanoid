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

#include <Utils/Audio/Sound.hpp>

#include <Utils/Graphics/Texture.hpp>

#include <Utils/FreeType/Font.hpp>

using namespace std;

using namespace Engine;

using namespace Utils;
using namespace Utils::Audio;
using namespace Utils::Graphics;
using namespace Utils::FreeType;



World::World() {

    try {

        resourceManager_ = ResourceManager::getInstance();

    } catch (const runtime_error&) {}

}



World::~World() {

    BOOST_FOREACH(boost::shared_ptr<Texture> texture, textures_) {

        resourceManager_->deleteResource<Texture>(texture);

    }

    BOOST_FOREACH(boost::shared_ptr<FreeType::Font> font, fonts_) {

        resourceManager_->deleteResource<FreeType::Font>(font);

    }

    BOOST_FOREACH(boost::shared_ptr<Sound> sound, sounds_) {

        resourceManager_->deleteResource<Sound>(sound);

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
