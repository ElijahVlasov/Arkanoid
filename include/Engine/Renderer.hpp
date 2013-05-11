/*******************************************

    Рендерер игры. Инкапсулирует работу
    с OpenGL и отрисовку сцены.

*******************************************/

#ifndef _SALT2D_ENGINE_RENDERER_HPP
#define _SALT2D_ENGINE_RENDERER_HPP

#include <stdexcept>

#include <Engine/Game.hpp>

#include <Utils/Singleton.hpp>

namespace Engine {
	
	class Renderer: public Utils::Singleton<Renderer> {
	
		SINGLETON(Renderer)

		public:

			void onRender();

			void onResize(unsigned int width, unsigned int height);

		protected:

			Renderer() throw(std::runtime_error);
			~Renderer();

		private:

			Game* game_;
			
			void initGL(unsigned int width, unsigned int height);

	};

}



#endif
