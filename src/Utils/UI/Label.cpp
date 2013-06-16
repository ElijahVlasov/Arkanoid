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

    setDrawEvent(boost::bind(boost::mem_fn(&Label::onDraw), this, _1));

}



Label::~Label() {}



void Label::onDraw(Event&) {

    drawText();

}



void Label::drawText() {

    float x       =  static_cast<float>(getX());
    float y       =  static_cast<float>(getY());
    float width   =  static_cast<float>(getWidth());
    float height  =  static_cast<float>(getHeight());

    // рендерим текст
    try {

        getFont().renderText(getText(), x, y, width, height);

    } catch(const runtime_error&) {}

}
