#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Utils/UI/Component.hpp>
#include <Utils/UI/Event.hpp>
#include <Utils/UI/Label.hpp>

using namespace std;

using namespace Utils;
using namespace Utils::UI;



Label::Label() throw(runtime_error):
    Component()
{

    setDrawEvent( &Label::onDraw );

}



Label::~Label() {}



void Label::onDraw(Component* sender, Event&) {

    auto l = dynamic_cast<Label*>(sender);

    l->drawText();

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
