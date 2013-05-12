/*****************************************************************
 
                Главный класс приложения. 


*****************************************************************/

#ifndef _SALT2D_GAME_HPP
#define _SALT2D_GAME_HPP

#include <stdexcept>

#include <Engine/SaltEngine.hpp>
#include <Engine/GameStates/IGameState.hpp>

#include <Utils/MouseButton.hpp>
#include <Utils/Singleton.hpp>

namespace Engine {
	
    class Game: public Utils::Singleton<Game> {

        SINGLETON(Game)

        public:
	
            void onRender();

            void onKeyDown(int key);
            void onKeyUp(int key);

            void onMouseMotion(int x, int y);
            void onMouseDown(int x, int y, Utils::MouseButton mouseButton);
            void onMouseUp(int x, int y, Utils::MouseButton mouseButton);

            void setScreenRect(unsigned int width, unsigned int height);

            int getScreenWidth() const;
            int getScreenHeight() const;

            const GameStates::IGameState* getState() const;
            void setState(GameStates::IGameState* state);

            void setRunning(bool isRunning);
            bool isRunning() const;

        protected:

            Game();
            ~Game();

        private:

            bool isRunning_;

            GameStates::IGameState* state_;

            unsigned int scrWidth_, scrHeight_;

    };

}

#endif
