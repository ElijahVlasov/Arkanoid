#ifndef _SALT2D_UTILS_UI_LABEL_HPP
#define _SALT2D_UTILS_UI_LABEL_HPP

#include <stdexcept>

#include <Utils/UI/Component.hpp>

namespace Utils {

	namespace UI {
	
		class Label: public Component {

			public:

				Label() throw(std::runtime_error);
				~Label();

				void draw();

			private:

				void drawText();
		
		};

	}

}

#endif