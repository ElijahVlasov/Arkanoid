#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>

#include <Utils.hpp>

#include <Utils/UI/Menu.hpp>

using namespace std;

using namespace Utils;
using namespace Utils::UI;



Menu::Menu() throw(runtime_error):
    Component()
{

    setDrawEvent(boost::bind(boost::mem_fn(&Menu::onDraw), this, _1));

}



Menu::~Menu() {}



void Menu::addComponent(const boost::shared_ptr<Component>& component) {

    components_.push_back(component);

}



const std::list<boost::shared_ptr<Component>>& Menu::getComponents() const {

    return components_;

}



void Menu::mouseDown(int x, int y, MouseButton btn) {

    BOOST_FOREACH(boost::shared_ptr<Component> component, components_) {

        if(!component->isContains(x, y)) {
            continue;
        }

        // переводим в локальные координаты
        // для компонента
        int componentX = component->getX();
        int componentY = component->getY();

        component->mouseDown(componentX - x, componentY - y, btn);

    }

    Component::mouseDown(x, y, btn);

}



void Menu::mouseUp(int x, int y, MouseButton btn) {

    BOOST_FOREACH(boost::shared_ptr<Component> component, components_) {

        if(!component->isContains(x, y)) {
            continue;
        }

        // переводим в локальные координаты
        // для компонента
        int componentX = component->getX();
        int componentY = component->getY();

        component->mouseUp(componentX - x, componentY - y, btn);

    }

    Component::mouseUp(x, y, btn);

}



void Menu::hoverMouse(int x, int y) {

    BOOST_FOREACH(boost::shared_ptr<Component> component, components_) {

        if(!component->isContains(x, y)) {
            continue;
        }

        // переводим в локальные координаты
        // для компонента
        int componentX = component->getX();
        int componentY = component->getY();

        component->hoverMouse(componentX - x, componentY - y);

    }

    Component::hoverMouse(x, y);

}



void Menu::keyDown(int key) {

    BOOST_FOREACH(boost::shared_ptr<Component> component, components_) {
        component->keyDown(key);
    }

    Component::keyDown(key);

}



void Menu::keyUp(int key) {

    BOOST_FOREACH(boost::shared_ptr<Component> component, components_) {
        component->keyUp(key);
    }

    Component::keyUp(key);

}



void Menu::onDraw(Event&) {

    drawSelf();
    drawComponents();

}



void Menu::drawComponents() {

    BOOST_FOREACH(boost::shared_ptr<Component> component, components_) {
        component->draw();
    }

}



void Menu::drawSelf() {

    float x       =  static_cast<float>(getX());
    float y       =  static_cast<float>(getY());
    float width   =  static_cast<float>(getWidth());
    float height  =  static_cast<float>(getHeight());

    Graphics::DrawTexture(
        x,
        y,
        width,
        height,
        background_
    );

}



void Menu::setBackground(const Texture& background) {

    background_ = background;

}



const Texture& Menu::getBackground() const {

    return background_;

}



void Menu::setBackgroundColor(const Color& color) {

    backgroundColor_ = color;

}



const Utils::Color& Menu::getBackgroundColor() const {

    return backgroundColor_;

}
