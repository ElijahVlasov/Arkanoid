#ifndef _SALT2D_ENGINE_GAMESTATES_GAMESTATE_HPP
#define _SALT2D_ENGINE_GAMESTATES_GAMESTATE_HPP

#include <Utils/MouseButton.hpp>

namespace Engine {

    namespace GameStates {

        /** Интерфейс состояния игры.
        */

        class IGameState {

            public:

                /** Перерисовка.
                */

                virtual void onRender() = 0;

                /** Событие изменения рамера окна.
                */

                virtual void onResize(unsigned int width, unsigned int height) = 0;

                /** Событие нажатия клавиши.
                  * @param key Код клавиши (все коды хранятся в SDL/SDL_keysym.h)
                */

                virtual void onKeyDown(int key) = 0;

                /** Событие отпускания клавиши.
                  * @param key Код клавиши (все коды хранятся в SDL/SDL_keysym.h)
                */

                virtual void onKeyUp(int key) = 0;

                virtual void onMouseMotion(int x, int y) = 0;
                virtual void onMouseDown(int x, int y, Utils::MouseButton mouseButton) = 0;
                virtual void onMouseUp(int x, int y, Utils::MouseButton mouseButton) = 0;

        };

    }

}

#endif
