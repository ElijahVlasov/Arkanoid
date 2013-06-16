#include <stdexcept>

#include <boost/bind.hpp>

#include <Utils.hpp>

#include <Utils/UI/Label.hpp>

using namespace std;

using namespace Utils;
using namespace Utils::FreeType;
using namespace Utils::UI;



Label::Label() throw(runtime_error):
    Component()
{

    setDrawEvent(boost::)

}



Label::~Label() {}



void Label::onDraw(Event&) {

    drawText();

}



void Label::drawText() {

    float x       =  static_cast<float>(getX());
    float y       =  static_cast<float>(getY());
    /*float width   =  static_cast<float>(getWidth());
    float height  =  static_cast<float>(getHeight());

    Texture text;*/

    // рендерим текст
    try {

        /*text = */getFont().renderText(getText(), x, y);

    } catch(const invalid_argument&) {

    } catch(const runtime_error&) {

    }

    /*float textWidth   =  text.getWidth();
    float textHeight  =  text.getHeight();

    // если текст больше Label'а, то "обрезаем" его:

    if(textWidth > width) {

        textWidth = width;

    }

    if(textHeight > height) {
	
        textHeight = height;

    }

    Graphics::DrawTexture(
        x,
        y,
        textWidth,
        textHeight,
        text
    );*/

}
