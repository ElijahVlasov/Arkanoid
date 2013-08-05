#include <stdexcept>

#include <boost/bind.hpp>
#include <boost/mem_fn.hpp>
#include <boost/shared_ptr.hpp>

#include <Utils/Color.hpp>

#include <Utils/Graphics/GraphicsManager.hpp>
#include <Utils/Graphics/Texture.hpp>

#include <Utils/UI/Container.hpp>
#include <Utils/UI/Menu.hpp>

using namespace std;

using namespace Utils;

using namespace Utils::Graphics;

using namespace Utils::UI;



Menu::Menu() throw(runtime_error):
    Container()
{

    const Color defColor = {1.0f, 1.0f, 1.0f, 0.0f};

    backgroundColor_ = defColor;

}



Menu::~Menu() {}



void Menu::drawSelf() {

    GraphicsManager::ClearScreen(backgroundColor_);

    if(background_ == 0) {
        return;
    }

    GraphicsManager::DrawTexture(
        getBoxI(),
        *background_
    );

}



void Menu::setBackground(const boost::shared_ptr<Texture>& background) {

    background_ = background;

}



const boost::shared_ptr<Texture>& Menu::getBackground() const {

    return background_;

}



void Menu::setBackgroundColor(const Color& color) {

    backgroundColor_ = color;

}



const Utils::Color& Menu::getBackgroundColor() const {

    return backgroundColor_;

}
