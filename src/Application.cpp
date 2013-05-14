#include <boost/cstdint.hpp>

#include <stdexcept>
#include <string>

#include <SDL/SDL.h>

#include <Application.hpp>

#include <Engine/Game.hpp>

#include <Utils.hpp>

#include <boost/interprocess/shared_memory_object.hpp>

using namespace boost::interprocess;

using namespace std;

using Utils::MouseButton;

using Engine::Game;



Application::Application() throw(runtime_error):
    game_(Game::getInstance()),
    surface_(0)       
{
	
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
    
    // «адаем иконку и заголовок окна
    ::SDL_WM_SetCaption(name, 0);

	
    // «адаем параметры OpenGL
    ::SDL_GL_SetAttribute(SDL_GL_RED_SIZE,        8);
    ::SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,      8);
    ::SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,       8);
    ::SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,      8);
 
    ::SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      16);
    ::SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,     32);
 
    // под X11 не работает:
    // ::SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,    8);
    // ::SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,  8);
    // ::SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,   8);
    // ::SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,  8);
 
    ::SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
    ::SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

    setSurfaceSize(640, 480);

}



void Application::setSurfaceSize(unsigned int width, unsigned int height) throw(runtime_error) {
	
    if(surface_ != 0) { // удал€ем предыдущий surface
        ::SDL_FreeSurface(surface_);
    }

    surface_ = ::SDL_SetVideoMode(width, height, 32, SDL_FLAGS);

    ASSERT(
        (surface_ != 0),
        runtime_error(::SDL_GetError())
    );

}



int Application::run() throw(runtime_error) {

    SDL_Event event;

    game_->setRunning(true);

    while(game_->isRunning()) { 

        while(::SDL_PollEvent(&event)) { // неблокирующе, провер€ем наличие событий 

            OnEvent(&event);

        }

        OnRender();

    }

    return 0;

}



void Application::OnRender() {

	unsigned int scrWidth, scrHeight;


	// ѕровер€ем, было ли изменено разрешение экрана
	// в объекте Game

	scrWidth  = game_->getScreenWidth();
	scrHeight = game_->getScreenHeight();

	if( (scrWidth != static_cast<unsigned int>(surface_->w) )
		|| (scrHeight != static_cast<unsigned int>(surface_->h)) ) { // если измененно, то мен€ем размер surface'а
		
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
			
			// если приложение развертываетс€
			if(event->active.gain) {
				
				OnRestore();

			} else { // если свертываетс€
				
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
