#ifndef _SALT2D_ENGINE_GAMESTATES_LOADINGSTATE_HPP
#define _SALT2D_ENGINE_GAMESTATES_LOADINGSTATE_HPP

#include <thread>

#include <Engine/GameStates/IGameState.hpp>

namespace Engine {

    namespace GameStates {

        class LoadingState: public IGameState {

            public:

                template <class LoadingFunc> LoadingState(LoadingFunc loadingFunc);

                void onActive();
                void onRemove();

                void onRender();

                void onResize(unsigned int width, unsigned int height);

                void onKeyDown(int key);
                void onKeyUp(int key);

                void onMouseMotion(int x, int y);
                void onMouseDown(int x, int y, Utils::MouseButton mouseButton);
                void onMouseUp(int x, int y, Utils::MouseButton mouseButton);

            private:

                std::thread loadingThread_;

        };



        template <class LoadingFunc> LoadingState::LoadingState(LoadingFunc loadingFunc):
            loadingThread_(loadingFunc)
        {
            loadingThread_.detach();
        }

    }

}

#endif // _SALT2D_ENGINE_GAMESTATES_LOADINGSTATE_HPP
