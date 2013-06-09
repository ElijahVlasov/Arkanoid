#ifndef _SALT2D_LUAAPI_LUAAPI_HPP
#define _SALT2D_LUAAPI_LUAAPI_HPP

#include <stdexcept>

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

        protected:

            LuaAPI_();
            ~LuaAPI_();

        private:

            Engine::Game* game_;

            Utils::Lua* lua_;

            Utils::ResourceManager* resourceManager_;

            Utils::Audio* audio_;

    };

}

#endif
