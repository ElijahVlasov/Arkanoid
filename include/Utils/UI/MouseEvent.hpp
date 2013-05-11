#ifndef _SALT2D_UTILS_UI_MOUSEEVENT_HPP
#define _SALT2D_UTILS_UI_MOUSEEVENT_HPP

#include <Utils/MouseButton.hpp>

#include <Utils/UI/Event.hpp>

namespace Utils {

	namespace UI {
	
		struct MouseEvent: public Event {
		
			int x, y;

			Utils::MouseButton mouseButton;

		};

	}

}

#endif