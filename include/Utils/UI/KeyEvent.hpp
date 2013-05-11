#ifndef _SALT2D_UTILS_UI_KEYEVENT_HPP
#define _SALT2D_UTILS_UI_KEYEVENT_HPP

#include <Utils/UI/Event.hpp>

namespace Utils {

	namespace UI {
	
		struct KeyEvent: public Event {
		
			int key;

		};

	}

}


#endif