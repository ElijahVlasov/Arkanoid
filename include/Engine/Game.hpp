#ifndef _SALT2D_ENGINE_GAME_HPP
#define _SALT2D_ENGINE_GAME_HPP

#include <stdexcept>

#include <Engine/SaltEngine.hpp>
#include <Engine/GameStates.hpp>

#include <Utils/Graphics.hpp>
#include <Utils/MouseButton.hpp>
#include <Utils/Singleton.hpp>

namespace Engine {

    /** Главный класс игры.
      * Инкапсулирует загрузку ресурсов,
      * прорисовку, синглплеер, мультиплеер и др.
      * @author Elijah Vlasov
    */
	
    class Game: public Utils::Singleton<Game> {

        SINGLETON(Game)

        public:
        
            /** Создать объект игры.
            */
	
            static Game* Create() throw(std::runtime_error);
            
            /** Отрисовка всего.
            */

            void onRender();
            
            /** Клавиша зажата.
            */

            void onKeyDown(int key);
            
            /** Клавиша отпущена.
            */
            
            void onKeyUp(int key);
            
            /** Передвижение курсора.
            */

            void onMouseMotion(int x, int y);
            
            /** Зажата кнопка мыши.
            */
            
            void onMouseDown(int x, int y, Utils::MouseButton mouseButton);
            
            /** Отпущена кнопка мыши.
            */
            
            void onMouseUp(int x, int y, Utils::MouseButton mouseButton);

            /** Установить размер окна.
            */
            
            void setScreenRect(unsigned int width, unsigned int height);
            
            /** Ширина окна.
            */

            int getScreenWidth() const;
            
            /** Высота окна.
            */
            
            int getScreenHeight() const;
            
            /** Состояние игры.
            */

            const GameStates::IGameState* getState() const;
            
            /** Установить состояние игры.
            */
            
            void setState(GameStates::IGameState* state);

            /** Запустить игру.
            */
            
            void run();
            
            /** Завершить игру.
            */
            
            void quit();            

            /** Запущено ли приложения.
            */
            
            bool isRunning() const;

        protected:

            Game() throw(std::runtime_error);
            ~Game();

        private:

            void loadingThread();

            Utils::Graphics* graphics_;

            GameStates::StartLogoState*  startLogoState_;
            GameStates::MenuState*       menuGameState_;
            GameStates::SingleGameState* singleGameState_;

            bool isRunning_;

            GameStates::IGameState* state_;

            unsigned int scrWidth_, scrHeight_;

    };

}

#endif

namespace Engine {

    class Game;

}
