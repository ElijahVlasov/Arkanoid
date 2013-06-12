#include <cmath>

#include <exception>

#include <boost/shared_ptr.hpp>

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include <Engine.hpp>
#include <Utils.hpp>

#include <LuaAPI.hpp>
#include <LuaAPI/LuaAPI.hpp>

using namespace luabind;

using namespace Engine;

using namespace LuaAPI;

using namespace Utils;



LuaAPI_::LuaAPI_():
    game_(Game::getInstance()),
    lua_(Lua::getInstance()),
    resourceManager_(ResourceManager::getInstance()),
    audio_(Audio::getInstance())
{

    lua_State* L = lua_->getLuaState();

    module(L, "system")
    [

        class_<LuaAPI_>("direction")
            .enum_("")
                [

                    value("up",     Direction::UP),
                    value("down",   Direction::DOWN),
                    value("right",  Direction::RIGHT),
                    value("left",  Direction::LEFT)

                ],

        class_<Texture>("texture")
            .property("name",   &Texture::getName)
            .property("width",  &Texture::getWidth,  &Texture::setWidth)
            .property("height", &Texture::getHeight, &Texture::setHeight),

        class_<Sound>("sound"),

        def("sound",        LuaAPI_::System_LoadSound),
        def("texture",      LuaAPI_::System_LoadTexture),
        def("play_sound",   LuaAPI_::System_PlaySound),
        def("draw_texture", LuaAPI_::System_DrawTexture),
        def("exit",         LuaAPI_::System_Quit)

    ];

}



LuaAPI_::~LuaAPI_() {

    if(game_ != 0) {
        game_->Free();
    }

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



void LuaAPI_::System_LoadScript(const char* name) {

    instance_->lua_->loadScript(name);

}



boost::shared_ptr<Sound> LuaAPI_::System_LoadSound(const char* name) {

    try {

        boost::shared_ptr<Resource> soundResource = instance_->resourceManager_->getResource(ResourceLoader::ResourceType::SOUND, name);

        return boost::dynamic_pointer_cast<Sound>(soundResource);

    } catch(const std::exception&) {}

    return boost::shared_ptr<Sound>();

}



boost::shared_ptr<Texture> LuaAPI_::System_LoadTexture(const char* name)  {

    try {

        boost::shared_ptr<Resource> textureResource = instance_->resourceManager_->getResource(ResourceLoader::ResourceType::TEXTURE, name);

        return boost::dynamic_pointer_cast<Texture>(textureResource);

    } catch(const std::exception&) {}

    return boost::shared_ptr<Texture>();

}



void LuaAPI_::System_PlaySound(const boost::shared_ptr<Sound>& sound) {

    instance_->audio_->playSound(*sound);

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



void LuaAPI_::System_Quit() {

    instance_->game_->quit();

}