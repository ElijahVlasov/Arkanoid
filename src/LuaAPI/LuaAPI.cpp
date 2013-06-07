#include <boost/shared_ptr.hpp>

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include <Engine.hpp>
#include <Utils.hpp>

#include <LuaAPI.hpp>
#include <LuaAPI/LuaAPI.hpp>

using namespace Engine;

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



void LuaAPI_::System_PlayAudio(const boost::shared_ptr<Sound>& sound) {

    audio_->playSound(*sound);

}



void LuaAPI_::System_DrawTexture(float x, float y, const boost::shared_ptr<Texture>& texture, Direction direction) {

    Graphics::CoordArray coordAr;

    switch (direction)
    {

        case Engine::UP: {

            coordAr = Graphics::UP_COORDS;

        }
        break;

        case Engine::DOWN:{

            coordAr = Graphics::DOWN_COORDS;

        }
        break;

        case Engine::RIGHT:{

            coordAr = Graphics::RIGHT_COORDS;

        }
        break;

        case Engine::LEFT:{

            coordAr = Graphics::LEFT_COORDS;

        }
        break;

    }

    Graphics::DrawTexture(x, y, texture->getWidth(), texture->getHeight(), coordAr, *texture);

}