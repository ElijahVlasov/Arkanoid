#ifndef _SALT2D_UTILS_UI_LABEL_HPP
#define _SALT2D_UTILS_UI_LABEL_HPP

#include <stdexcept>

#include <Utils/UI/Event.hpp>
#include <Utils/UI/Component.hpp>

namespace Utils {

    namespace UI {
	
        class Label: public Component {

            public:

                Label() throw(std::runtime_error);
                ~Label();

            protected:

                void onDraw(Event&);

            private:

                void drawText();
		
        };

    }

}

#endif
