#ifndef _SALT2D_UTILS_UI_MENU_HPP
#define _SALT2D_UTILS_UI_MENU_HPP

#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Utils/Color.hpp>
#include <Utils/Texture.hpp>

#include <Utils/UI/Container.hpp>

namespace Utils {

    namespace UI {

        /** Меню.
          * @author Elijah Vlasov
        */

        class Menu: public Container {

            public:

                Menu() throw(std::runtime_error);
                ~Menu();

                void setBackground(const boost::shared_ptr<Texture>& background);

                /** Фоновая текстура.
                */

                const boost::shared_ptr<Texture>& getBackground() const;

                /** Установить фоновый цвет.
                */

                void setBackgroundColor(const Color& color);

                /** Фоновый цвет.
                */

                const Color& getBackgroundColor() const;

            protected:

                void drawSelf();

            private:

                Color backgroundColor_;

                boost::shared_ptr<Texture> background_;

        };

	}

}

#endif
