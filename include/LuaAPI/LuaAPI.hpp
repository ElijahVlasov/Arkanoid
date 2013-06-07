#ifndef _SALT2D_LUAAPI_LUAAPI_HPP
#define _SALT2D_LUAAPI_LUAAPI_HPP

#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Engine/Direction.hpp>

#include <Utils.hpp>

namespace LuaAPI {

    class LuaAPI_: public Utils::Singleton<LuaAPI_> {

        SINGLETON(LuaAPI_)

        public:

            boost::shared_ptr<Utils::Sound> System_LoadAudio(const char* name);
            void System_PlayAudio(const boost::shared_ptr<Utils::Sound>& sound);

            boost::shared_ptr<Utils::Texture> System_LoadTexture(const char* name);
            void System_DrawTexture(float x, float y, const boost::shared_ptr<Utils::Texture>& texture, Engine::Direction textureDirection);

            void System_ShowDialog(const char* name);
            void System_ShowMenu(const char* name);

            void System_Quit();

        protected:

            LuaAPI_();
            ~LuaAPI_();

        private:

            Utils::Lua* lua_;

            Utils::ResourceManager* resourceManager_;

            Utils::Audio* audio_;

    };

}

#endif
