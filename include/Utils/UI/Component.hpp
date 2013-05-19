#ifndef _SALT2D_UTILS_UI_COMPONENT_HPP
#define _SALT2D_UTILS_UI_COMPONENT_HPP

#include <stdexcept>
#include <string>

#include <boost/function.hpp>

#include <Utils/FreeType.hpp>
#include <Utils/MouseButton.hpp>

#include <Utils/UI/Event.hpp>
#include <Utils/UI/KeyEvent.hpp>
#include <Utils/UI/MouseEvent.hpp>

namespace Utils {

    namespace UI {

        /** Базовый класс для всех компонентов GUI.
		  * @author Elijah Vlasov
        */

        class Component {

            public:

                /** Делегат зажатия кнопки мыши.
                */
                
                typedef boost::function<void (MouseEvent& event)> MouseDownEvent;
                
                /** Делегат отпускания кнопки мыши.
                */
                
                typedef boost::function<void (MouseEvent& event)> MouseUpEvent;
                
                /** Делегат клика мышкой(Зажатие и отпускание по одной точке).
                */
                
                typedef boost::function<void (MouseEvent& event)> MouseClickEvent;
                
                /** Делегат наведения курсора на компонент.
                */
                
                typedef boost::function<void (MouseEvent& event)> MouseHoverEvent;

                /** Делегат перерисовки компонента.
                */
                
                typedef boost::function<void (Event&)> DrawEvent;

                /** Делегат зажатия клавиши.
                */
                
                typedef boost::function<void (KeyEvent)> KeyUpEvent;
                
                /** Делегат отпускания клавиши.
                */
                
                typedef boost::function<void (KeyEvent)> KeyDownEvent;

                Component() throw(std::runtime_error);
                virtual ~Component() = 0;

                /** Устанавить прямоугольник компонента.
                */
                void setRect(int x, int y, unsigned int width, unsigned int height);

                /** X-координата.
                */
                
                int getX() const;
                
                /** Y-координата
                */
                
                int getY() const;
                
                /** Ширина компонента.
                */
                
                unsigned int getWidth() const;
                
                /** Высота компонента.
                */
                
                unsigned int getHeight() const;

                /** Установить текст компонента.
                  * @param text текст. Если равен NULL, то текст устанавливается
                  *        пустой строкой
                */
                
                void setText(const char* text);
                
                /** Установить текст.
                */
                
                void setText(const std::string& text);
                
                /** Текст компонента.
                */ 
                
                const std::string& getText() const;

                /** Установить имя компонента.
                  * @param name Имя компонента. Если равно NULL, то текст устанавливается
                  *             пустой строкой                  
                */
                
                void setName(const char* name);
                
                /** Установить имя компонента.
                */
                
                void setName(const std::string& name);
                
                /** Имя компонента.
                */ 
                
                const std::string& getName() const;

                /** Установить шрифт.
                */
                
                void setFont(const Utils::FreeType::Font& font);
                
                /** Шрифт компонента.
                */
                
                Utils::FreeType::Font getFont() const;

                /** Принадлежит ли точка компоненту.
                  * @return true, если точка (x;y) содерржится
                  *         в компоненте
                */
                virtual bool isContains(int x, int y);

                /** Мышь зажата на компоненте.
                */
                
                virtual void mouseDown(int x, int y, MouseButton btn);
                
                /** Мышь отпущена на компоненте.
                */
                
                virtual void mouseUp(int x, int y, MouseButton btn);

                /** Клик по компоненту.
                  * Автоматически вызывается, если были последовательно вызваны
                  * mouseDown и mouseUp с одинаковыми координатами и кнопкой BUTTON_LEFT
                */
                
                virtual void click(int x, int y);

                /** Наведение мыши на компонент.
                */
                
                virtual void hoverMouse(int x, int y);

                /** Клавиша зажата.
                */
                
                virtual void keyDown(int key);
                
                /** Клавиша отпущена. 
                */
                
                virtual void keyUp(int key);

                /** Прорисовка компонента.
                */
                
                virtual void draw();
				
                /** Установить MouseHoverEvent.
                */
                
                void setHoveredEvent(const MouseHoverEvent& eventHandler);
                
                /** Установить MouseClickEvent.
                */
                
                void setClickedEvent(const MouseClickEvent& eventHandler);
                
                /** Установить MouseDownEvent
                */
                
                void setMouseDownEvent(const MouseDownEvent& eventHandler);
                
                /** Установить MouseUpEvent.
                */
                
                void setMouseUpEvent(const MouseUpEvent& eventHandler);

                /** Установить DrawEvent.
                */
                
                void setDrawEvent(const DrawEvent& eventHandler);

                /** Установить KeyDownEvent.
                */
                
                void setKeyDownEvent(const KeyDownEvent& eventHandler);
                
                /** Установить KeyUpEvent.
                */
                
                void setKeyUpEvent(const KeyUpEvent& eventHandler);

            private:

                Utils::FreeType::Font font_;

                std::string text_;

                std::string name_;

                int x_, y_;
                unsigned int width_, height_;

                MouseDownEvent    mouseDownEvent_;
                MouseUpEvent      mouseUpEvent_;
                MouseHoverEvent   hoverEvent_;
                MouseClickEvent   clickEvent_;

                DrawEvent         drawEvent_;
	
                KeyDownEvent      keyDownEvent_;
                KeyUpEvent        keyUpEvent_;

                int mouseDownX_, mouseDownY_;

        };

    }

}

#endif
