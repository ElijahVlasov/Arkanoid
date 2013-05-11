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

				void setRect(int x, int y, unsigned int width, unsigned int height);

				int getX() const;
				int getY() const;
				unsigned int getWidth() const;
				unsigned int getHeight() const;

				void setText(const char* text);
				void setText(const std::string& text);
				const std::string& getText() const;

				void setName(const char* name);
				void setName(const std::string& text);
				const std::string& getName() const;

				void setFont(const Utils::FreeType::Font& font);
				Utils::FreeType::Font getFont() const;

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
				
				void setHoveredEvent(const MouseHoverEvent& eventHandler);
				void setClickedEvent(const MouseClickEvent& eventHandler);
				void setMouseDownEvent(const MouseDownEvent& eventHandler);
				void setMouseUpEvent(const MouseUpEvent& eventHandler);

				void setDrawEvent(const DrawEvent& eventHandler);

				void setKeyDownEvent(const KeyDownEvent& eventHandler);
				void setKeyUpEvent(const KeyUpEvent& eventHandler);

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