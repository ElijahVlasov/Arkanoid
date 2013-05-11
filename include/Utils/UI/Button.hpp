/****************************************

			Класс кнопки.

*****************************************/

#ifndef _SALT2D_UTILS_UI_BUTTON_HPP
#define _SALT2D_UTILS_UI_BUTTON_HPP

#include <stdexcept>
#include <string>

#include <boost/function.hpp>

#include <Utils/MouseButton.hpp>
#include <Utils/Texture.hpp>

#include <Utils/UI/Component.hpp>

namespace Utils {

	namespace UI {
	
		class Button: public Component {
		
			public:

				Button() throw(std::runtime_error);
				~Button();

				void mouseDown(int x, int y, Utils::MouseButton btn);
				void mouseUp(int x, int y, Utils::MouseButton btn);

				void draw();

			private:

				void drawTexture();
				void drawText();

				Texture curTexture_;

				Texture defTexture_;

				Texture clickedTexture_;

				Texture hoveredTexture_;

		};

	}

}

#endif