/*

	Интерфейс состояния игры

*/
#ifndef _SALT2D_ENGINE_GAMESTATES_GAMESTATE_HPP
#define _SALT2D_ENGINE_GAMESTATES_GAMESTATE_HPP

#include <Utils/MouseButton.hpp>

namespace Engine {

	namespace GameStates {
		
		class IGameState {
	
			public:

				virtual void onRender() = 0;
				
				virtual void onResize(unsigned int width, unsigned int height) = 0;

				virtual void onKeyDown(int key) = 0;
				virtual void onKeyUp(int key) = 0;

				virtual void onMouseMotion(int x, int y) = 0;
				virtual void onMouseDown(int x, int y, Utils::MouseButton mouseButton) = 0;
				virtual void onMouseUp(int x, int y, Utils::MouseButton mouseButton) = 0;

		};

	}

}

#endif