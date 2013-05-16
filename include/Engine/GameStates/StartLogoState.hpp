#ifndef _SALT2D_ENGINE_GAMESTATES_STARTLOGOSTATE_HPP
#define _SALT2D_ENGINE_GAMESTATES_STARTLOGOSTATE_HPP

#include <stdexcept>

#include <Engine/Game.hpp>

#include <Engine/GameStates/IGameState.hpp>

#include <Utils/Texture.hpp>
#include <Utils/Singleton.hpp>

namespace Engine {

    namespace GameStates {

        class StartLogoState: public Utils::Singleton<StartLogoState>,
                                     public IGameState {

            SINGLETON(StartLogoState)

            public:

                void onRender();

                void onResize(unsigned int width, unsigned int height);

                void onKeyDown(int key);
                void onKeyUp(int key);

                void onMouseMotion(int x, int y);
                void onMouseDown(int x, int y, Utils::MouseButton mouseButton);
                void onMouseUp(int x, int y, Utils::MouseButton mouseButton);

            protected:

                StartLogoState() throw(std::runtime_error);
             //   ~StartLogoState();

            private:

                /*Engine::*/Game* game_; 

                Utils::Texture logo_;

        };

    }

}

#endif

namespace Engine {
 
    namespace GameState {

        class StartLogoState;

    }

}