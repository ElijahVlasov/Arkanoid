#include <list>

#include <boost/shared_ptr.hpp>

#include <Utils/UI/Component.hpp>
#include <Utils/UI/Container.hpp>
#include <Utils/UI/Event.hpp>

using namespace std;

using namespace Utils::UI;



Container::Container():
    Component()
{

    setDrawEvent( &Container::onDraw );

}



const Container::children_list& Container::getComponents() const {

    return components_;

}

void Container::addComponent(Container::children_ptr component) {

    components_.push_back(component);

}



void Container::keyUp(int key) {

    BOOST_FOREACH(Container::children_ptr child, components_) {

        child->keyUp(key);

    }

    Component::keyUp(key);

}



void Container::keyDown(int key) {

    BOOST_FOREACH(Container::children_ptr child, components_) {

        child->keyDown(key);

    }

    Component::keyDown(key);

}



void Container::mouseMotion(int x, int y) {

    BOOST_FOREACH(Container::children_ptr child, components_) {

        child->mouseMotion(x, y);

    }

    Component::mouseMotion(x, y);

}



void Container::mouseUp(int x, int y, MouseButton btn) {

    BOOST_FOREACH(Container::children_ptr child, components_) {

        child->setPressed(false);

        if(!child->isContains(x, y)) {
            continue;
        }

        int relX = x - child->getX();
        int relY = y - child->getY();

        child->mouseUp(relX, relY, btn);

    }

    Component::mouseUp(x, y, btn);

}



void Container::mouseDown(int x, int y, MouseButton btn) {

    BOOST_FOREACH(Container::children_ptr child, components_) {

        if(!child->isContains(x, y)) {
            continue;
        }

        int relX = x - child->getX();
        int relY = y - child->getY();

        child->mouseDown(relX, relY, btn);

    }

    Component::mouseDown(x, y, btn);

}



void Container::onDraw(Component* sender, Event&) {

    auto containerSender = dynamic_cast<Container*>(sender);

    containerSender->drawSelf();
    containerSender->drawChildren();

}



void Container::drawChildren() {

    BOOST_FOREACH(Container::children_ptr child, components_) {

        child->draw();

    }

}
