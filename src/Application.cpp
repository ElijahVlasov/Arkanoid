#include <boost/cstdint.hpp>

#include <exception>
#include <stdexcept>
#include <string>

#include <SDL/SDL.h>

#include <Application.hpp>

#include <Engine/Game.hpp>

#include <Engine/GameStates.hpp>

#include <Utils/MouseButton.hpp>

#include "config.h"

using namespace std;

using namespace Engine::GameStates;

using Utils::MouseButton;

using Engine::Game;



Application::Application() throw(runtime_error):
    isFullscreen_(false),
    surface_(0)
{

    initSDL(800, 600, Salt2D_PROJECT_NAME);

}



Application::~Application() {

    ::SDL_Quit();

}



void Application::initSDL(unsigned int width, unsigned int height, const char* name) {

    ASSERT(
        (::SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0),
        runtime_error("Can't load SDL library!")
    );

    // Задаем иконку и заголовок окна
    ::SDL_WM_SetCaption(name, 0);


    // Задаем параметры OpenGL
    ::SDL_GL_SetAttribute(SDL_GL_RED_SIZE,        8);
    ::SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,      8);
    ::SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,       8);
    ::SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,      8);


    ::SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      16);
    ::SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,     32);
 /**/
    // под X11 не работает:
    // ::SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,    8);
    // ::SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,  8);
    // ::SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,   8);
    // ::SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,  8);

    //::SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
    //::SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);
    setSurfaceSize(640, 480);

}



void Application::setSurfaceSize(unsigned int width, unsigned int height) throw(std::runtime_error) {

    uint32_t flags = SDL_FLAGS;

    if(surface_ != 0) { // удаляем предыдущий surface
        ::SDL_FreeSurface(surface_);
    }

    if(isFullscreen_) {
        flags |= SDL_FULLSCREEN;
    }

    surface_ = ::SDL_SetVideoMode(width, height, 32, flags);

    ASSERT(
        (surface_ != 0),
        runtime_error(::SDL_GetError())
    );

}



int Application::run() throw(std::exception) {

    SDL_Event event;

    resourceLoader_ = Utils::PCResourceLoader::getInstance();

    game_ = Game::Create(resourceLoader_.get());

    game_->setScreenRect(640, 480);

    game_->run();

    while(game_->isRunning()) {

        while(::SDL_PollEvent(&event)) { // неблокирующе, проверяем наличие событий

            OnEvent(&event);

        }

        OnRender();

        OnLoop();

    }

    return 0;

}



void Application::OnLoop() throw(std::exception) {

    game_->onLoop();

}



void Application::OnRender() {

    unsigned int scrWidth, scrHeight;


    // Проверяем, было ли изменено разрешение экрана
    // в объекте Game

    scrWidth  = game_->getScreenWidth();
    scrHeight = game_->getScreenHeight();

    if( (scrWidth != static_cast<unsigned int>(surface_->w) )
        || (scrHeight != static_cast<unsigned int>(surface_->h)) ) { // если измененно, то меняем размер surface'а

        setSurfaceSize(scrWidth, scrHeight);

    }

    game_->onRender();

    ::SDL_GL_SwapBuffers();

}



void Application::OnMinimize() {



}



void Application::OnRestore() {



}



void Application::OnKeyUp(SDLKey key, SDLMod mod, Uint16 unicode) {

    if(key == SDLK_F11) {

        isFullscreen_ = !isFullscreen_;
        setSurfaceSize(surface_->w, surface_->h);

    } else {

        game_->onKeyUp(static_cast<int>(key));

    }

}



void Application::OnKeyDown(SDLKey key, SDLMod mod, Uint16 unicode) {


    game_->onKeyDown(static_cast<int>(key));

}



void Application::OnMouseDown(int x, int y, uint8_t button) {

    MouseButton btn;

    switch(button) {

        case SDL_BUTTON_LEFT:{

            btn = MouseButton::BUTTON_LEFT;

        }
        break;

        case SDL_BUTTON_RIGHT:{

            btn = MouseButton::BUTTON_RIGHT;

        }
        break;

        case SDL_BUTTON_MIDDLE:{

            btn = MouseButton::BUTTON_MIDDLE;

        }
        break;

    }

    game_->onMouseDown(x, game_->getScreenHeight() - y, btn);

}



void Application::OnMouseUp(int x, int y, uint8_t button) {

    MouseButton btn;

    switch(button) {

        case SDL_BUTTON_LEFT:{

            btn = MouseButton::BUTTON_LEFT;

        }
        break;

        case SDL_BUTTON_RIGHT:{

            btn = MouseButton::BUTTON_RIGHT;

        }
        break;

        case SDL_BUTTON_MIDDLE:{

            btn = MouseButton::BUTTON_MIDDLE;

        }
        break;

    }

    game_->onMouseUp(x, game_->getScreenHeight() - y, btn);

}



void Application::OnMouseMotion(int x, int y) {

    game_->onMouseMotion(x, game_->getScreenHeight() - y);

}



void Application::OnQuit() {

    game_->quit();

}



void Application::OnEvent(SDL_Event* event) {

    switch(event->type) {

        case SDL_QUIT: { // по закрытию

            OnQuit();

        }
        break;

        case SDL_ACTIVEEVENT: {

            if(event->active.state != SDL_APPACTIVE) {
                return;
            }

            // если приложение развертывается
            if(event->active.gain) {

                OnRestore();

            } else { // если свертывается

                OnMinimize();

            }

        }
        break;

        case SDL_KEYDOWN: { // по нажатию клавиши

            OnKeyDown(event->key.keysym.sym,
                        event->key.keysym.mod,
                            event->key.keysym.unicode);

        }
        break;

        case SDL_KEYUP: { // по отпусканию клавиши

            OnKeyUp(event->key.keysym.sym,
                        event->key.keysym.mod,
                            event->key.keysym.unicode);

        }
        break;

        case SDL_MOUSEMOTION: {

            OnMouseMotion(event->motion.x, event->motion.y);

        }
        break;

        case SDL_MOUSEBUTTONDOWN: {

            OnMouseDown(event->button.x, event->button.y, event->button.button);

        }
        break;

        case SDL_MOUSEBUTTONUP: {

            OnMouseUp(event->button.x, event->button.y, event->button.button);

        }
        break;

    }

}
