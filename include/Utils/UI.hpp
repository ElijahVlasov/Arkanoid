#ifndef _SALT2D_UTILS_UI_HPP
#define _SALT2D_UTILS_UI_HPP

#include <Utils/UI/Button.hpp>
#include <Utils/UI/Component.hpp>
#include <Utils/UI/ComponentEvent_wrapper.hpp>
#include <Utils/UI/ComponentFactory.hpp>
#include <Utils/UI/Event.hpp>
#include <Utils/UI/KeyEvent.hpp>
#include <Utils/UI/Label.hpp>
#include <Utils/UI/Menu.hpp>
#include <Utils/UI/MenuFactory.hpp>
#include <Utils/UI/MouseEvent.hpp>

#endif



namespace Utils {

    /** Классы для создания графических элементов интерфейса.
      * @author Elijah Vlasov
    */

    namespace UI {

        class Button;
        class Component;
        template<class EventType> class ComponentEvent_wrapper;
        class ComponentFactory;
        class Event;
        struct KeyEvent;
        class Label;
        class Menu;
        class MenuFactory;
        struct MouseEvent;

    }

}
