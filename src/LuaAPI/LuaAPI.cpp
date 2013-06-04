#include <boost/shared_ptr.hpp>

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include <Utils.hpp>

#include <LuaAPI.hpp>
#include <LuaAPI/LuaAPI.hpp>

using namespace LuaAPI;

using namespace Utils;



LuaAPI_::LuaAPI_():
    lua_(Lua::getInstance()),
    resourceManager_(ResourceManager::getInstance()),
    audio_(Audio::getInstance())
{

    

}



LuaAPI_::~LuaAPI_() {

    if(lua_ != 0) {
        lua_->Free();
    }

    if(resourceManager_ != 0) {
        resourceManager_->Free();
    }

    if(audio_ != 0) {
        audio_->Free();
    }

}



boost::shared_ptr<Sound> LuaAPI_::System_LoadAudio(const char* name) {

    try {

        boost::shared_ptr<Resource> soundResource = resourceManager_->getResource(ResourceLoader::ResourceType::SOUND, name);

        return boost::dynamic_pointer_cast<Sound>(soundResource);

    } catch(...) {}

    return boost::shared_ptr<Sound>();

}



boost::shared_ptr<Texture> LuaAPI_::System_LoadTexture(const char* name)  {

    try {

        boost::shared_ptr<Resource> textureResource = resourceManager_->getResource(ResourceLoader::ResourceType::TEXTURE, name);

        return boost::dynamic_pointer_cast<Texture>(textureResource);

    } catch(...) {}

    return boost::shared_ptr<Texture>();

}
