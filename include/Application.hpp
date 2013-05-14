/*****************************************

	Класс, инкапсулирующий все 
	взаимодействие с системой.

*****************************************/


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

        Application() throw(std::runtime_error);
        ~Application();

        int run() throw(std::runtime_error);

        void OnEvent(SDL_Event* event);
	
        void OnRender();

        void OnQuit();
		
        void OnRestore();

        void OnMinimize();

        void OnKeyUp(SDLKey key, SDLMod mod, Uint16 unicode);

        void OnKeyDown(SDLKey key, SDLMod mod, Uint16 unicode);	

        void OnMouseDown(int x, int y, uint8_t button);
        void OnMouseUp(int x, int y, uint8_t button);

        void OnMouseMotion(int x, int y);

    private:

        void initSDL(unsigned int width, unsigned int height, const char* name);

        void setSurfaceSize(unsigned int width, unsigned int height) throw(std::runtime_error);

        static const uint32_t SDL_FLAGS = SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL;

        bool isFullscreen_;

        Engine::Game* game_;

        Engine::GameStates::MenuState*       menuGameState_;
        Engine::GameStates::SingleGameState* singleGameState_;

        SDL_Surface* surface_;

        bool isRunning_;

};

#endif
