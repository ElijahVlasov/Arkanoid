#include <mutex>

#include <boost/shared_ptr.hpp>

#include <Engine/Direction.hpp>
#include <Engine/IController.hpp>
#include <Engine/DynamicObject.hpp>

using namespace Engine;



const float DynamicObject::MIN_MOVE = 4.5f;



DynamicObject::DynamicObject():
    isMoving_(false)
{}



void DynamicObject::setController(const boost::shared_ptr<IController>& controller) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    controller_ = controller;

}



void DynamicObject::onCollision(const ObjectPtr& object) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    isMoving_ = false;

}



void DynamicObject::live() {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    float xMoving = 0.0f;
    float yMoving = 0.0f;

    if(controller_->getUpState()) {

        if(!controller_->getDownState()) {

            yMoving = MIN_MOVE;

        }

    } else if(controller_->getDownState()) {

        yMoving = -MIN_MOVE;

    }

    if(controller_->getLeftState()) {

        if(!controller_->getRightState()) {

            xMoving = -MIN_MOVE;

        }

    } else if(controller_->getRightState()) {

        xMoving = MIN_MOVE;

    }

    if((xMoving != 0.0f) && (yMoving != 0.0f)) {

        if(isMoving_) {

            isMoving_ = false;

            this->onEndMoving();

            return;

        }

    }

    if(!isMoving_) {

        isMoving_ = true;

        this->onStartMoving();

    }

    move(xMoving, yMoving);

}

