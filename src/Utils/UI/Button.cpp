#include <cmath>

#include <stdexcept>
#include <string>

#include <boost/bind.hpp>

#include <boost/function.hpp>

#include <Utils.hpp>

using namespace std;

using namespace boost;

using namespace Utils;

using namespace Utils::UI;



Button::Button() throw(runtime_error):
    Component()
{

    setDrawEvent(boost::bind(boost::mem_fn(&Button::onDraw), this, _1));

}



Button::~Button() {}



void Button::onDraw(Event&) {

    drawTexture();
    drawText();

    Component::draw();

}



void Button::drawTexture() {

    float x       =  static_cast<float>(getX());
    float y       =  static_cast<float>(getY());
    float width   =  static_cast<float>(getWidth());
    float height  =  static_cast<float>(getHeight());

    Graphics::DrawTexture(
        x,
        y,
        width,
        height,
        curTexture_
    );

}



void Button::drawText() {

    float x       =  static_cast<float>(getX());
    float y       =  static_cast<float>(getY());

    // рендерим текст
    try {

        getFont().renderText(getText(), x, y);

    } catch(const invalid_argument&) {

    } catch(const runtime_error&) {

    }


    /*float textWidth   =  static_cast<float>(text.getWidth());
    float textHeight  =  static_cast<float>(text.getHeight());

    float textX, textY;

    // получаем величину отступа от края кнопки
    textX = abs(width  -  textWidth)  / 2;
    textY = abs(height -  textHeight) / 2;

    if(textWidth >= width) { 
	
        textX = x - textX; // текст выходит за край кнопки

    } else {
	
        textX = x + textX; // не выходит

    }

    // аналогично
    if(textHeight >= height) {
	
        textY = y - textY;

    } else {
	
        textY = y + textY;

    }

    Graphics::DrawTexture(
        textX,
        textY,
        textWidth,
        textHeight,
        text
    );*/

}



void Button::mouseDown(int x, int y, Utils::MouseButton btn) {

    curTexture_ = clickedTexture_;

    Component::mouseDown(x, y, btn);

}



void Button::mouseUp(int x, int y, Utils::MouseButton btn) {

    curTexture_ = defTexture_;

    Component::mouseUp(x, y, btn);

}
