#ifndef _SALT2D_LUAAPI_LUAAPI_HPP
#define _SALT2D_LUAAPI_LUAAPI_HPP

#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Engine/Game.hpp>

#include <Utils.hpp>

#include "geometry_defines.hpp"

namespace LuaAPI {

    class LuaAPI_: public Utils::Singleton<LuaAPI_> {

        SINGLETON(LuaAPI_)

        public:

            static void System_LoadScript(const char* name);

            static boost::shared_ptr<Utils::Audio::Sound> System_LoadSound(const char* name);
            static boost::shared_ptr<Utils::Audio::SoundPlayer> System_CreateSoundPlayer(const boost::shared_ptr<Utils::Audio::Sound>& sound);

            static boost::shared_ptr<Utils::Graphics::Texture> System_LoadTexture(const char* name);
            //static void System_DrawTexture(float x, float y, const boost::shared_ptr<Utils::Texture>& texture, Engine::Direction textureDirection);

            static boost::shared_ptr<Utils::FreeType::Font> System_LoadFont(const char* name);

            static void System_ShowDialog(const char* name);
            static void System_ShowMenu(const char* name);

            static unsigned int System_GetScreenWidth();
            static unsigned int System_GetScreenHeight();
            static void System_SetScreenRect(unsigned int width, unsigned int height);

            static boost::shared_ptr<Utils::UI::Menu> System_GetMainMenu();
            static boost::shared_ptr<Utils::UI::Menu> System_GetPauseMenu();

            static void System_StartGame();
            static void System_QuitGame();

            static void System_Quit();

            static Utils::SingletonPointer<Engine::Game> Engine_GetGame();

        protected:

            LuaAPI_();

        private:

            template <class Geometry>
            static void Graphics_DrawTexture(const Geometry& geometry, boost::shared_ptr<Utils::Graphics::Texture> texture) {

                Utils::Graphics::GraphicsManager::DrawTexture(geometry, *texture);

            }



            template <class PolygonType>
            static void Polygon_addPoint(PolygonType& polygon, const typename PolygonType::point_type& point) {

                polygon.outer().push_back(point);

            }



            class Lua_BoxSetters {

                public:

                    template <class BoxType, class PointType>
                    static void setMinCorner(BoxType& box, const PointType& point) {

                            box.min_corner() = point;

                    }



                    template <class BoxType, class PointType>
                    static void setMaxCorner(BoxType& box, const PointType& point) {

                            box.max_corner() = point;

                    }

            };


            class Lua_ComponentSetters {

                public:

                    static void setMouseMotionEvent(    boost::shared_ptr<Utils::UI::Component> component, luabind::object eventHandler);
                    static void setHoveredEvent(        boost::shared_ptr<Utils::UI::Component> component, luabind::object eventHandler);
                    static void setLeavedEvent(         boost::shared_ptr<Utils::UI::Component> component, luabind::object eventHandler);
                    static void setClickedEvent(        boost::shared_ptr<Utils::UI::Component> component, luabind::object eventHandler);
                    static void setMouseDownEvent(      boost::shared_ptr<Utils::UI::Component> component, luabind::object eventHandler);
                    static void setMouseUpEvent(        boost::shared_ptr<Utils::UI::Component> component, luabind::object eventHandler);
                    static void setDrawEvent(           boost::shared_ptr<Utils::UI::Component> component, luabind::object eventHandler);
                    static void setKeyDownEvent(        boost::shared_ptr<Utils::UI::Component> component, luabind::object eventHandler);
                    static void setKeyUpEvent(          boost::shared_ptr<Utils::UI::Component> component, luabind::object eventHandler);

            };

            Utils::SingletonPointer<Engine::Game> game_;

            Utils::SingletonPointer<Engine::GameStates::MenuState> menuGameState_;

            Utils::SingletonPointer<Utils::Lua> lua_;

            Utils::SingletonPointer<Utils::ResourceManager> resourceManager_;

            Utils::SingletonPointer<Utils::Audio::AudioManager> audioManager_;

    };

}

#endif
