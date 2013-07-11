#include <cmath>

#include <functional>
#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/FreeType.hpp>
#include <Utils/Graphics.hpp>
#include <Utils/MouseButton.hpp>
#include <Utils/Resource.hpp>
#include <Utils/ResourceManager.hpp>
#include <Utils/SingletonPointer.hpp>
#include <Utils/Texture.hpp>

#include <Utils/UI/Button.hpp>

using namespace std;

using namespace boost;

using namespace Utils;
using namespace Utils::UI;
using namespace Utils::FreeType;



Button::Button() throw(runtime_error):
    Component()
{

    try {

    	SingletonPointer<ResourceManager> resourceManager = ResourceManager::getInstance();

        boost::shared_ptr<Resource> defTextureResource     = resourceManager->getResource(ResourceManager::ResourceType::TEXTURE, "textures/ui/button.png");
        boost::shared_ptr<Resource> clickedTextureResource = resourceManager->getResource(ResourceManager::ResourceType::TEXTURE, "textures/ui/button_clicked.png");
        boost::shared_ptr<Resource> hoveredTextureResource = resourceManager->getResource(ResourceManager::ResourceType::TEXTURE, "textures/ui/button_hovered.png");

        defTexture_     = boost::dynamic_pointer_cast<Texture>(defTextureResource);
        clickedTexture_ = boost::dynamic_pointer_cast<Texture>(clickedTextureResource);
        hoveredTexture_ = boost::dynamic_pointer_cast<Texture>(hoveredTextureResource);

    } catch(const bad_alloc&) {}

    curTexture_ = defTexture_;

    setDrawEvent( &Button::onDraw );

}



Button::~Button() {}



void Button::onDraw(Component* sender, Event&) {

    auto b = dynamic_cast<Button*>(sender);

    b->drawTexture();
    b->drawText();

}



void Button::drawTexture() {

    Graphics::DrawTexture(
        getBoxI(),
        *curTexture_
    );

}



void Button::drawText() {

    float x       =  static_cast<float>(getX());
    float y       =  static_cast<float>(getY());
    float width   =  static_cast<float>(getWidth());
    float height  =  static_cast<float>(getHeight());

    // рендерим текст
    try {

        Font::FONT_RECT rect = getFont().measureText(getText());

        float xOffset = 0.0f;
        float yOffset = 0.0f;

        if(rect.width <= width) {

            xOffset = (width - rect.width) / 2;

            width = -1.0f;

        }

        if(rect.height <= height) {

            yOffset = (height - rect.height) / 2;

            height = -1.0f;

        }

        getFont().renderText(getText(), x + xOffset, y + yOffset, width, height);

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
