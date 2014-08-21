#include <boost/cstdint.hpp>
#include <boost/format.hpp>

#include <exception>
#include <locale>
#include <stdexcept>
#include <string>

#include <SDL/SDL.h>

#include <Application.hpp>

#include <Engine/Game.hpp>

#include <Engine/GameStates.hpp>

#include <Utils/LocalizationManager.hpp>
#include <Utils/MouseButton.hpp>
#include <Utils/PCResourceLoader.hpp>
#include <Utils/ResourceManager.hpp>

#include "config.h"

using namespace std;

using namespace Engine::GameStates;

using namespace Utils;

using Engine::Game;



Application::Application() throw(runtime_error):
    isFullscreen_(false),
    localizationManager_(LocalizationManager::getInstance()),
    resourceLoader_(PCResourceLoader::getInstance()),
    resourceManager_(ResourceManager::getInstance())
{

	resourceManager_->setResourceLoader(resourceLoader_.get());

	setLocale();

    initSDL(
        640, 480,
        (boost::format("%1% v%2%.%3%")
            % PROJECT_NAME
            % VERSION_MAJOR
            % VERSION_MINOR
        ).str().c_str()
    );

}



Application::~Application() {

    ::SDL_Quit();

}



void Application::initSDL(unsigned int width, unsigned int height, const char* name) {

    ASSERT(
        (::SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0),
        runtime_error("Can't load SDL library!")
    );

    string iconName = (boost::format("%1%/icon.bmp")
        % RESOURCE_PATH
    ).str();

    Uint32          colorkey;
    SDL_Surface     *image;

    image = ::SDL_LoadBMP(iconName.c_str());

    //colorkey = ::SDL_MapRGBA(image->format, 255, 255, 255, 255);

    ::SDL_SetColorKey(image, SDL_TRUE, colorkey);

    window_ = ::SDL_CreateWindow(name,
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            width, height,
                            SDL_WINDOW_OPENGL);

    ::SDL_SetWindowIcon(window_, image);
    ::SDL_GL_CreateContext(window_);

    // Задаем параметры OpenGL
    /*::SDL_GL_SetAttribute(SDL_GL_RED_SIZE,        8);
    ::SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,      8);
    ::SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,       8);
    ::SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,      8);


    ::SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      16);
    ::SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,     32);*/
 /**/
    // под X11 не работает:
    // ::SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,    8);
    // ::SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,  8);
    // ::SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,   8);
    // ::SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,  8);

    //::SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
    //::SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);
    //setSurfaceSize(width, height);

}



void Application::setSurfaceSize(unsigned int width, unsigned int height) throw(std::runtime_error) {

    /*uint32_t flags = SDL_FLAGS;

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
    );*/

}



void Application::setLocale() throw(runtime_error) {

	string localeName = locale("").name();

    try {

        size_t point = localeName.find('.');

        if(point == string::npos) {

            localizationManager_->setLocale(localeName);

            return;

        }

        localeName.erase(point);

        localizationManager_->setLocale(localeName);

    } catch(const runtime_error&) {

        localizationManager_->setLocale("en_US");

    }

}



int Application::run() throw(std::exception) {

    SDL_Event event;

    game_ = Game::Create();

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

    /*if( (scrWidth != static_cast<unsigned int>(surface_->w) )
        || (scrHeight != static_cast<unsigned int>(surface_->h)) ) { // если измененно, то меняем размер surface'а

        setSurfaceSize(scrWidth, scrHeight);

    }*/
    ::SDL_SetWindowSize(window_, scrWidth, scrHeight);

    game_->onRender();

    ::SDL_GL_SwapWindow(window_);

}



void Application::OnMinimize() {



}



void Application::OnRestore() {



}



void Application::OnKeyUp(SDL_Keycode key, Uint16 mod) {

    if(key == SDLK_F11) {

        if(!isFullscreen_ ) {

            ::SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
            isFullscreen_ = true;

        } else {

            ::SDL_SetWindowFullscreen(window_, 0);
            isFullscreen_ = false;

        }

    } else {

        game_->onKeyUp(static_cast<int>(key));

    }

}



void Application::OnKeyDown(SDL_Keycode key, Uint16 mod) {


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

        case SDL_WINDOWEVENT: {

            switch (event->window.event) {

                case SDL_WINDOWEVENT_SHOWN:

                    OnRestore();
                    break;

                case SDL_WINDOWEVENT_HIDDEN:

                    OnMinimize();
                    break;

            }

        }
        break;

        case SDL_KEYDOWN: { // по нажатию клавиши

            OnKeyDown(event->key.keysym.sym,
                            event->key.keysym.mod);

        }
        break;

        case SDL_KEYUP: { // по отпусканию клавиши

            OnKeyUp(event->key.keysym.sym,
                            event->key.keysym.mod);

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
