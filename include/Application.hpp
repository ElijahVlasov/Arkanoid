/** Инициализационный класс приложения. Создает 
  * окно приложения и обрабатывает сообщения системы. 
  * Использует SDL.
*/

#ifndef _SALT2D_APPLICATION_HPP
#define _SALT2D_APPLICATION_HPP

#include <boost/cstdint.hpp>

#include <stdexcept>
#include <string>

#include <SDL/SDL.h>

#include <Engine/Game.hpp>

#include <Engine/GameStates.hpp>

#include <boost/utility.hpp>

class Application: public boost::noncopyable {

    public:

        /** Инициализация окна приложения и графического режима.
          * @throw Генерирует std::runtime_error, если произошли ошибки
          * инициализации SDL.
        */        
       
        Application() throw(std::runtime_error);
        ~Application();

        /** Запуск процесса обработки сообщений.
          * @throw Генерирует std::runtime_error, если произошла внутриигровая ошибка
        */

        int run() throw(std::runtime_error);

        /** Обработка SDL-события.
          *
        */

        void OnEvent(SDL_Event* event);

        /** Событие отрисовки.
        */

        void OnRender();

        /** Завершение приложения.
        */

        void OnQuit();

        /** Событие разворачивания окна
        */

        void OnRestore();

        /** Событие сворачивания окна
        */

        void OnMinimize();

        /** Клавиша зажата.
          * @param key код клавиши
          * @param mod модификатор нажатия
          * @param unicode Юникодовый транслированный символ клавиши
        */

        void OnKeyUp(SDLKey key, SDLMod mod, Uint16 unicode);

        /** Клавиша отпущена.
          * @param key код клавиши
          * @param mod модификатор нажатия
          * @param unicode Юникодовый транслированный символ клавиши
        */

        void OnKeyDown(SDLKey key, SDLMod mod, Uint16 unicode);

        /** Кнопка мыши зажата.
          * @param x координата курсора
          * @param y координата курсора
          * @param button кнопка мыши
        */

        void OnMouseDown(int x, int y, uint8_t button);

        /** Кнопка мыши отпущена.
          * @param x координата курсора
          * @param y координата курсора
          * @param button кнопка мыши
        */

        void OnMouseUp(int x, int y, uint8_t button);

        /** Событие движения мыши.
          * @param x новая координата курсора
          * @param y новая координата курсора
        */

        void OnMouseMotion(int x, int y);

    private:

        void initSDL(unsigned int width, unsigned int height, const char* name);

        void setSurfaceSize(unsigned int width, unsigned int height) throw(std::runtime_error);

        static const boost::uint32_t SDL_FLAGS = SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL;

        bool isFullscreen_;

        Engine::Game* game_;

        SDL_Surface* surface_;

        bool isRunning_;

};

#endif
