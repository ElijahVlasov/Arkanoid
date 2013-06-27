#ifndef _SALT2D_LUAAPI_LUAAPI_HPP
#define _SALT2D_LUAAPI_LUAAPI_HPP

#include <stdexcept>

#include <boost/intrusive_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <Engine/Game.hpp>
#include <Engine/Direction.hpp>

#include <Utils.hpp>

namespace LuaAPI {

    class LuaAPI_: public Utils::Singleton<LuaAPI_> {

        SINGLETON(LuaAPI_)

        public:

            static void System_LoadScript(const char* name);

            static boost::shared_ptr<Utils::Sound> System_LoadSound(const char* name);
            static void System_PlaySound(const boost::shared_ptr<Utils::Sound>& sound);

            static boost::shared_ptr<Utils::Texture> System_LoadTexture(const char* name);
            static void System_DrawTexture(float x, float y, const boost::shared_ptr<Utils::Texture>& texture, Engine::Direction textureDirection);

            static void System_ShowDialog(const char* name);
            static void System_ShowMenu(const char* name);

            static void System_Quit();

            static boost::intrusive_ptr<Engine::Game> Engine_GetGame();

        protected:

            LuaAPI_();

        private:

            

            class Lua_ComponentSetters {

                public:

                    static void setHoveredEvent(  boost::shared_ptr<Utils::UI::Component> component, luabind::object eventHandler);
                    static void setClickedEvent(  boost::shared_ptr<Utils::UI::Component> component, luabind::object eventHandler);
                    static void setMouseDownEvent(boost::shared_ptr<Utils::UI::Component> component, luabind::object eventHandler);
                    static void setMouseUpEvent(  boost::shared_ptr<Utils::UI::Component> component, luabind::object eventHandler);
                    static void setDrawEvent(     boost::shared_ptr<Utils::UI::Component> component, luabind::object eventHandler);
                    static void setKeyDownEvent(  boost::shared_ptr<Utils::UI::Component> component, luabind::object eventHandler);
                    static void setKeyUpEvent(    boost::shared_ptr<Utils::UI::Component> component, luabind::object eventHandler);

            };

            boost::intrusive_ptr<Engine::Game> game_;

            boost::intrusive_ptr<Engine::GameStates::MenuState> menuGameState_;

            boost::intrusive_ptr<Utils::Lua> lua_;

            boost::intrusive_ptr<Utils::ResourceManager> resourceManager_;

            boost::intrusive_ptr<Utils::Audio> audio_;

    };

}

#endif
