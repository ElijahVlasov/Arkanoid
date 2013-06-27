#ifndef _SALT2D_ENGINE_GAMESTATES_SINGLEGAMESTATE_HPP
#define _SALT2D_ENGINE_GAMESTATES_SINGLEGAMESTATE_HPP

#include <stdexcept>

#include <boost/intrusive_ptr.hpp>

#include <Engine/Renderer.hpp>

#include <Engine/GameStates/IGameState.hpp>
#include <Engine/GameStates/MenuState.hpp>

#include <Utils/Lua.hpp>
#include <Utils/Singleton.hpp>

namespace Engine {

    class Game;

    namespace GameStates {

        class SingleGameState: public Utils::Singleton<SingleGameState>,
                                    public IGameState {

            SINGLETON(SingleGameState)

            public:

                void quit();

                void onActive();
                void onRemove();

                void onRender();

                void onResize(unsigned int width, unsigned int height);

                void onKeyDown(int key);
                void onKeyUp(int key);

                void onMouseMotion(int x, int y);
                void onMouseDown(int x, int y, Utils::MouseButton mouseButton);
                void onMouseUp(int x, int y, Utils::MouseButton mouseButton);

            protected:

                SingleGameState() throw(std::runtime_error);

            private:

                void showDebugInfo();
                void makeScreenshot();

                boost::intrusive_ptr<Engine::Game>       game_;

                boost::intrusive_ptr<Utils::Lua>        lua_;

                boost::intrusive_ptr<MenuState>          menuState_;

        };

    }

}

#endif
