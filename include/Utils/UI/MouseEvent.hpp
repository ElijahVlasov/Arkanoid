#ifndef _SALT2D_UTILS_UI_MOUSEEVENT_HPP
#define _SALT2D_UTILS_UI_MOUSEEVENT_HPP

#include <Utils/MouseButton.hpp>

#include <Utils/UI/Event.hpp>

namespace Utils {

    namespace UI {
    
        /** Событие мыши.
          * @author Elijah Vlasov
        */
	
        struct MouseEvent: public Event {
		
            int x; /**< X-координата курсора */
            int y; /**< Y-координата курсора */

            Utils::MouseButton mouseButton; /**< Кнопка мыши */

        };

    }

}

#endif