/****************************************

	Базовый класс для создания UI.

*****************************************/


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
	
		class Component {
		
			public:

				// события, связаннные с нажатием мыши
				typedef boost::function<void (MouseEvent& event)> MouseDownEvent;
				typedef boost::function<void (MouseEvent& event)> MouseUpEvent;
				typedef boost::function<void (MouseEvent& event)> MouseClickEvent;
				typedef boost::function<void (MouseEvent& event)> MouseHoverEvent;

				// событие перерисовки
				typedef boost::function<void (Event&)> DrawEvent;

				// события, связанные с клавиатурой
				typedef boost::function<void (KeyEvent)> KeyUpEvent;
				typedef boost::function<void (KeyEvent)> KeyDownEvent;

				Component() throw(std::runtime_error);
				virtual ~Component() = 0;

				virtual void setRect(int x, int y, unsigned int width, unsigned int height);

				virtual int getX() const;
				virtual int getY() const;
				virtual unsigned int getWidth() const;
				virtual unsigned int getHeight() const;

				virtual void setText(const char* text);
				virtual void setText(const std::string& text);
				virtual const std::string& getText() const;

				virtual void setName(const char* name);
				virtual void setName(const std::string& text);
				virtual const std::string& getName() const;

				virtual void setFont(const Utils::FreeType::Font& font);
				virtual Utils::FreeType::Font getFont() const;

				// возвращает true, если прямоугольник 
				// компонента, содержит (x;y)
				virtual bool isContains(int x, int y);

				virtual void mouseDown(int x, int y, MouseButton btn);
				virtual void mouseUp(int x, int y, MouseButton btn);

				// клик вызывается, если были последовательно
				// вызваны mouseDown и mouseUp, с одинаковыми 
				// координатами
				virtual void click(int x, int y);

				virtual void hoverMouse(int x, int y);

				virtual void keyDown(int key);
				virtual void keyUp(int key);

				virtual void draw();
				
				virtual void setHoveredEvent(const MouseHoverEvent& eventHandler);
				virtual void setClickedEvent(const MouseClickEvent& eventHandler);
				virtual void setMouseDownEvent(const MouseDownEvent& eventHandler);
				virtual void setMouseUpEvent(const MouseUpEvent& eventHandler);

				virtual void setDrawEvent(const DrawEvent& eventHandler);

				virtual void setKeyDownEvent(const KeyDownEvent& eventHandler);
				virtual void setKeyUpEvent(const KeyUpEvent& eventHandler);

			private:

				Utils::FreeType::Font font_;

				std::string text_;

				std::string name_;

				int x_, y_;
				unsigned int width_, height_;

				MouseDownEvent		mouseDownEvent_;
				MouseUpEvent		mouseUpEvent_;
				MouseHoverEvent		hoverEvent_;
				MouseClickEvent		clickEvent_;

				DrawEvent			drawEvent_;
	
				KeyDownEvent		keyDownEvent_;
				KeyUpEvent			keyUpEvent_;

				int mouseDownX_, mouseDownY_;

		};

	}

}

#endif
