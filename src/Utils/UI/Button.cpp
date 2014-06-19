#include <cmath>

#include <functional>
#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/FreeType.hpp>
#include <Utils/MouseButton.hpp>
#include <Utils/Resource.hpp>
#include <Utils/ResourceManager.hpp>
#include <Utils/SingletonPointer.hpp>

#include <Utils/Graphics/GraphicsManager.hpp>
#include <Utils/Graphics/Texture.hpp>

#include <Utils/UI/Button.hpp>

using namespace std;

using namespace boost;

using namespace Utils;
using namespace Utils::Graphics;
using namespace Utils::UI;
using namespace Utils::FreeType;



Button::Button() throw(runtime_error):
    Component()
{

    SingletonPointer<ResourceManager> resourceManager = ResourceManager::getInstance();

    defTexture_     = resourceManager->getResource<Texture>("textures/ui/button.png");
    clickedTexture_ = resourceManager->getResource<Texture>("textures/ui/button_clicked.png");
    hoveredTexture_ = resourceManager->getResource<Texture>("textures/ui/button_hovered.png");

    setDrawEvent( &Button::onDraw );

}



Button::~Button() {}



void Button::onDraw(Component* sender, Event&) {

    auto b = dynamic_cast<Button*>(sender);

    b->drawTexture();
    b->drawText();

}



void Button::drawTexture() {

    boost::shared_ptr<Texture> texture;

    if(isPressed()) {

        texture = clickedTexture_;

    } else if(isHovered()) {

        texture = hoveredTexture_;

    } else {

        texture = defTexture_;

    }

    GraphicsManager::DrawTexture(
        getBoxI(),
        *texture
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

            width = 10000.0f;

        }

        if(rect.height <= height) {

            yOffset = (height - rect.height) / 2;

            height = 10000.0f;

        }

        getFont().renderText(getText(), x + xOffset, y + yOffset, width, height);

    } catch(const runtime_error&) {}

}
