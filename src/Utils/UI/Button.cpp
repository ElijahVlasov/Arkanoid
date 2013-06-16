#include <cmath>

#include <stdexcept>
#include <string>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <Utils.hpp>

using namespace std;

using namespace boost;

using namespace Utils;
using namespace Utils::UI;
using namespace Utils::FreeType;



Button::Button() throw(runtime_error):
    Component(),
    resourceManager_(ResourceManager::getInstance()),
    curTexture_(defTexture_)
{

    try {

        boost::shared_ptr<Resource> defTextureResource     = resourceManager_->getResource(ResourceLoader::ResourceType::TEXTURE, "textures/ui/button.png");
        boost::shared_ptr<Resource> clickedTextureResource = resourceManager_->getResource(ResourceLoader::ResourceType::TEXTURE, "textures/ui/button_clicked.png");
        boost::shared_ptr<Resource> hoveredTextureResource = resourceManager_->getResource(ResourceLoader::ResourceType::TEXTURE, "textures/ui/button_hovered.png");

        defTexture_     = *boost::dynamic_pointer_cast<Texture>(defTextureResource);
        clickedTexture_ = *boost::dynamic_pointer_cast<Texture>(clickedTextureResource);
        hoveredTexture_ = *boost::dynamic_pointer_cast<Texture>(defTextureResource);

    } catch(const bad_alloc&) {}

    setDrawEvent(boost::bind(boost::mem_fn(&Button::onDraw), this, _1));

}



Button::~Button() {

    if(resourceManager_ != 0) {
        resourceManager_->Free();
    }

}



void Button::onDraw(Event&) {

    drawTexture();
    drawText();

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
    float width   =  static_cast<float>(getWidth());
    float height  =  static_cast<float>(getHeight());

    // рендерим текст
    try {

        Font::FONT_RECT rect = font.measureText(getText());

        if(rect.width <= width) {
            width = -1.0f;
        }

        if(rect.height <= height) {
            height = -1.0f;
        }

        font.renderText(getText(), x, y, width, height);

    } catch(const runtime_error&) {}

}



void Button::mouseDown(int x, int y, Utils::MouseButton btn) {

    curTexture_ = clickedTexture_;

    Component::mouseDown(x, y, btn);

}



void Button::mouseUp(int x, int y, Utils::MouseButton btn) {

    curTexture_ = defTexture_;

    Component::mouseUp(x, y, btn);

}
