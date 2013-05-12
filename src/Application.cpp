#include <boost/cstdint.hpp>

#include <stdexcept>
#include <string>

#include <SDL/SDL.h>

#include <Application.hpp>

#include <Exceptions/already_exist_error.hpp>

#include <Engine/Game.hpp>

#include <Utils.hpp>

#include <boost/interprocess/shared_memory_object.hpp>

using namespace boost::interprocess;

using namespace std;

using Utils::MouseButton;

using Engine::Game;



const string Application::SHARED_MEM_NAME = "SALT2D_ENGINE_SHARED_MEMORY_test_____12345";



Application::Application() throw(already_exist_error, runtime_error):
    game_(Game::getInstance()),
    sharedMem_(0),
    surface_(0)       
{
	
    // Создаем create_only shared_memory_object.
    // Если объект уже создан, значит, приложение уже
    // запущено.
    try {

        sharedMem_ = new shared_memory_object(create_only, SHARED_MEM_NAME.c_str(), read_write);
	
    } catch(...) {
		
        throw(already_exist_error(""));

    }
	
    initSDL(640, 480, "Shoter");

    game_->setScreenRect(640, 480);

}



Application::~Application() {

    if(game_ != 0) {
        game_->Free();
    }

    if(sharedMem_ != 0) {
        delete sharedMem_;
    }
	
    if(surface_ != 0) {
        ::SDL_FreeSurface(surface_);
    }

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
 
    ::SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,    8);
    ::SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,  8);
    ::SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,   8);
    ::SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,  8);
 
    ::SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
    ::SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

    // создаем SDL_Surface width * height
    setSurfaceSize(width, height);

}



void Application::setSurfaceSize(unsigned int width, unsigned int height) throw(runtime_error) {
	
    if(surface_ != 0) { // удаляем предыдущий surface
        ::SDL_FreeSurface(surface_);
    }

    surface_ = ::SDL_SetVideoMode(width, height, 32, SDL_FLAGS);

    ASSERT(
        (surface_ == 0),
        runtime_error(::SDL_GetError())
    );

}



int Application::run() throw(runtime_error) {

    SDL_Event event;

    game_->setRunning(true);

    while(game_->isRunning()) { 

        while(::SDL_PollEvent(&event)) { // неблокирующе, проверяем наличие событий 

            OnEvent(&event);

        }

        OnRender();

    }

    return 0;

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
		
	game_->onKeyUp(static_cast<int>(key));
	
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

	game_->onMouseDown(x, y, btn);

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

	game_->onMouseUp(x, y, btn);

}



void Application::OnMouseMotion(int x, int y) {

	game_->onMouseMotion(x, y);

}



void Application::OnQuit() {
	
	game_->setRunning(false);

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

	}
}
