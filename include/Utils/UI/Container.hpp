#ifndef _SALT2D_UTILS_UI_CONTAINER_HPP
#define _SALT2D_UTILS_UI_CONTAINER_HPP

#include <list>

#include <Utils/UI/Event.hpp>
#include <Utils/UI/Component.hpp>

namespace Utils {

    namespace UI {

        /** Базовый класс, для всех компонентов, содержащих
          * внутри себя другие компоненты.
          * @author Elijah Vlasov
        */

        class Container : public Component {

            public:

                typedef Component children_type;
                typedef boost::shared_ptr<children_type> children_ptr;
                typedef std::list<children_ptr> children_list;

                Container();

                /** Добавить компонент.
                */

                void addComponent(children_ptr component);

                /** Получить дочерние компоненты.
                */

                const children_list& getComponents() const;

                void mouseDown(int x, int y, MouseButton btn);
                void mouseUp(int x, int y, MouseButton btn);
                void mouseMotion(int x, int y);
                void keyDown(int key);
                void keyUp(int key);

            protected:

                static void onDraw(Component* sender, Event&);

                /** Отрисовка контейнера.
                  * Дочерние классы должны переопределять этот метод.
                */

                virtual void drawSelf() = 0;
                void drawChildren();

                children_list components_;

        };

    }

}

#endif
