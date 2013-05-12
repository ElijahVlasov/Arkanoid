#ifndef _SALT2D_ENGINE_GAMESTATES_SINGLEGAMESTATE_HPP
#define _SALT2D_ENGINE_GAMESTATES_SINGLEGAMESTATE_HPP

#include <stdexcept>

#include <Engine/Game.hpp>
#include <Engine/Renderer.hpp>

#include <Engine/GameStates/IGameState.hpp>
#include <Engine/GameStates/MenuState.hpp>

#include <Utils/Lua.hpp>
#include <Utils/Singleton.hpp>

namespace Engine {

	namespace GameStates {
	
		class SingleGameState: public Utils::Singleton<SingleGameState>,
										public IGameState {
		
			SINGLETON(SingleGameState)

			public:

				void onRender();

				void onResize(unsigned int width, unsigned int height);

				void onKeyDown(int key);
				void onKeyUp(int key);

				void onMouseMotion(int x, int y);
				void onMouseDown(int x, int y, Utils::MouseButton mouseButton);
				void onMouseUp(int x, int y, Utils::MouseButton mouseButton);

			protected:

				SingleGameState() throw(std::runtime_error);
				~SingleGameState();
			
			private:

				void showDebugInfo();
				void doScreenshot();

				Engine::Game*		game_;
				Engine::Renderer*	renderer_;

				Utils::Lua*			lua_;

				MenuState*			menuState_;

		};

	}

}

#endif