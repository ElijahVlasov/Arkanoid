﻿#ifndef _SALT2D_ENGINE_GAME_HPP
#define _SALT2D_ENGINE_GAME_HPP

#include <exception>
#include <mutex>
#include <stdexcept>
#include <thread>

#include <boost/shared_ptr.hpp>

#include <lua.hpp>

#include <Engine/SaltEngine.hpp>
#include <Engine/GameStates.hpp>

#include <LuaAPI.hpp>

#include <Utils/Graphics.hpp>
#include <Utils/Lua.hpp>
#include <Utils/MouseButton.hpp>
#include <Utils/ResourceLoader.hpp>
#include <Utils/ResourceManager.hpp>
#include <Utils/Singleton.hpp>
#include <Utils/SingletonPointer.hpp>

#include <Utils/UI/Menu.hpp>
#include <Utils/UI/MenuFactory.hpp>

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

            /** Завершение итерации цикла обработки сообщений.
            */

            void onLoop() throw(std::exception);

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

            void run() throw(std::runtime_error);

            /** Завершить игру.
            */

            void quit();

            /** Запущено ли приложения.
            */

            bool isRunning() const;

            void startGame(const char* worldName);
            void startGame(const std::string& worldName);

            void quitGame();

            boost::shared_ptr<Utils::UI::Menu> getMainMenu() const;
            boost::shared_ptr<Utils::UI::Menu> getPauseMenu() const;

        protected:

            Game() throw(std::runtime_error);
            ~Game();

        private:

            Utils::SingletonPointer<Utils::Lua>             lua_;

            Utils::SingletonPointer<LuaAPI::LuaAPI_>        luaAPI_;

            Utils::SingletonPointer<Utils::ResourceManager> resourceManager_;

            Utils::SingletonPointer<Utils::UI::MenuFactory> menuFactory_;

            boost::shared_ptr<Utils::UI::Menu> mainMenu_;
            boost::shared_ptr<Utils::UI::Menu> pauseMenu_;

            std::exception_ptr e_;

            mutable std::mutex   stateAccessMutex_;

            mutable std::mutex   exceptionCheckMutex_;  // мьютекс защиты e_
            mutable std::mutex   synchroMutex_;          // мьютекс защиты state_, scrWidth, scrHeight, isRunning

            mutable std::mutex   initMutex_; // нужен для синхронизации основного потока и потока загрузки
            std::thread* initThread_;

            // Установить текущее исключение(потом в главном потоке оно генерируется)
            void setException(const std::exception_ptr& e);
            const std::exception_ptr& getException();

            void loadResources();
            void loadMainMenu()  throw(std::runtime_error);
            void loadPauseMenu() throw(std::runtime_error);

            static int luaErrorHandler(lua_State* L);

            Utils::SingletonPointer<Utils::Graphics>             graphics_;

            Utils::SingletonPointer<GameStates::StartLogoState>  startLogoState_;
            Utils::SingletonPointer<GameStates::MenuState>       menuGameState_;
            Utils::SingletonPointer<GameStates::SingleGameState> singleGameState_;

            bool isRunning_;

            GameStates::IGameState* state_;

            unsigned int scrWidth_, scrHeight_;

    };

}

#endif
