#include <Engine/Object.hpp>

#include <Utils/Graphics/GraphicsManager.hpp>
#include <Utils/Graphics/Sprite.hpp>

using namespace Engine;

using namespace Utils::Graphics;


Object::~Object() {}



void Object::draw() {

    if(sprite_ == 0) {
        return;
    }

    sprite_->onRender(getRect());

}



void Object::setSprite(const boost::shared_ptr<Sprite>& sprite) {

    sprite_ = sprite;

}



const boost::shared_ptr<Sprite>& Object::getSprite() const {

    return sprite_;

}
