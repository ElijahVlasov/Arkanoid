#include <list>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#include <Utils/UI/Component.hpp>
#include <Utils/UI/Container.hpp>
#include <Utils/UI/Event.hpp>

using namespace std;

using namespace Utils::UI;



Container::Container():
    Component()
{

    setDrawEvent(boost::bind(boost::mem_fn(&Container::onDraw), this, _1));

}



const Container::children_list& Container::getComponents() const {

    return components_;

}

void Container::addComponent(const Container::children_ptr& component) {

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

        child->mouseUp(x, y, btn);

    }

    Component::mouseUp(x, y, btn);

}



void Container::mouseDown(int x, int y, MouseButton btn) {

    BOOST_FOREACH(Container::children_ptr child, components_) {

        child->mouseDown(x, y, btn);

    }

    Component::mouseDown(x, y, btn);

}



void Container::onDraw(Event&) {

    drawSelf();
    drawChildren();

}



void Container::drawChildren() {

    BOOST_FOREACH(Container::children_ptr child, components_) {

        child->draw();

    }

}
