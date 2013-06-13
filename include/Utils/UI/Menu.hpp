#ifndef _SALT2D_UTILS_UI_MENU_HPP
#define _SALT2D_UTILS_UI_MENU_HPP

#include <fstream>
#include <list>
#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/Color.hpp>

#include <Utils/UI/Component.hpp>

namespace Utils {

    namespace UI {
    
        /** Меню.
          * @author Elijah Vlasov 
        */

        class Menu: public Component {

            public:

                Menu() throw(std::runtime_error);

                ~Menu();
                
                /** Добавить компонент в меню.
                  * @param component boost::shared_ptr на компонент
                */

                void addComponent(const boost::shared_ptr<Component>& component);

                /** Список компонентов.
                */
                
                const std::list<boost::shared_ptr<Component>>& getComponents() const;

                void mouseDown(int x, int y, MouseButton btn);
                void mouseUp(int x, int y, MouseButton btn);

                void hoverMouse(int x, int y);

                void keyDown(int key);
                void keyUp(int key);

                /** Установить фоновую текстуру.
                */

                void setBackground(const Texture& background);
                
                /** Фоновая текстура.
                */
                
                const Texture& getBackground() const;
                
                /** Установить фоновый цвет.
                */

                void setBackgroundColor(const Color& color);
                
                /** Фоновый цвет.
                */
                
                const Color& getBackgroundColor() const;

            protected:

                void onDraw(Event&);

                void drawComponents();
                void drawSelf();

            private:

                Color backgroundColor_;

                Texture background_;

                std::list< boost::shared_ptr<Component> > components_;

        };

	}

}

#endif
