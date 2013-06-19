#ifndef _SALT2D_UTILS_UI_EVENT_HPP
#define _SALT2D_UTILS_UI_EVENT_HPP

#include <Utils/UI/Component.hpp>

namespace Utils {

	namespace UI {

        /** Событие UI.
          * @author Elijah Vlasov
        */

		struct Event {

            boost::shared_ptr<Component> sender;

		};

	}

}

#endif
