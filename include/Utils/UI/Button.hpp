#ifndef _SALT2D_UTILS_UI_BUTTON_HPP
#define _SALT2D_UTILS_UI_BUTTON_HPP

#include <stdexcept>
#include <string>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <Utils/MouseButton.hpp>
#include <Utils/ResourceManager.hpp>
#include <Utils/Texture.hpp>

#include <Utils/UI/Event.hpp>
#include <Utils/UI/Component.hpp>

namespace Utils {

    namespace UI {

        /** Класс кнопки.
        */

        class Button: public Component {

            public:

                Button() throw(std::runtime_error);
                ~Button();

                void mouseDown(int x, int y, Utils::MouseButton btn);
                void mouseUp(int x, int y, Utils::MouseButton btn);
                void mouseHover(int x, int y);
                void mouseLeave(int x, int y);

            protected:

                /** Прорисовка кнопки по-умолчанию.
                */

                static void onDraw(Component* sender, Event&);

                void drawTexture();
                void drawText();

            private:

                boost::shared_ptr<Texture> curTexture_, prevTexture_, defTexture_, clickedTexture_, hoveredTexture_;

        };

    }

}

#endif
