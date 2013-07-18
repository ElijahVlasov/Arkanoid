#include <mutex>

#include <boost/geometry.hpp>
#include <boost/shared_ptr.hpp>

#include <Engine/Collision.hpp>
#include <Engine/Direction.hpp>
#include <Engine/IController.hpp>
#include <Engine/DynamicObject.hpp>

#include "geometry_defines.hpp"

using namespace Engine;



const float DynamicObject::MIN_MOVE = 4.5f;



DynamicObject::DynamicObject():
    isMoving_(false)
{}



void DynamicObject::setController(const boost::shared_ptr<IController>& controller) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    controller_ = controller;

}



void DynamicObject::onCollision(const Collision& collision) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    if( isOnWay( collision.getSender() ) ) {
        isMoving_ = false;
    }

    isMoving_ = false;

}



void DynamicObject::live() {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    /*float xMoving = 0.0f;
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

    move(xMoving, yMoving);*/

}



bool DynamicObject::isOnWay(const ObjectPtr& object) const {

    namespace gd = GeometryDefines;

    typedef gd::Polygon::ring_type polygon_ring_type;

    // Полигон, описывающий путь, по которому пройдет объект.
    gd::Polygon wayPolygon;

    polygon_ring_type& wayOuter = wayPolygon.outer();

    auto objectPolygonIter = getPolygon().outer().rbegin();

    gd::Point leftUpObjectPoint  = *objectPolygonIter++;
    gd::Point rightUpObjectPoint = *objectPolygonIter;

    // Путь начинается там, где кончается объект.

    wayOuter.push_back(leftUpObjectPoint);
    wayOuter.push_back(rightUpObjectPoint);

    Object::DirectionVector direction = getDirectionVector();

    direction.x(direction.x() * MIN_MOVE);
    direction.y(direction.y() * MIN_MOVE);

    // Перемещаем конец объекта на direction и получаем точки конца объекта.

    gd::Point leftUpWayPoint(leftUpObjectPoint.x() + direction.x(), leftUpObjectPoint.y() + direction.y());
    gd::Point rightUpWayPoint(rightUpObjectPoint.x() + direction.x(), rightUpObjectPoint.y() + direction.y());

    wayOuter.push_back(rightUpWayPoint);
    wayOuter.push_back(leftUpWayPoint);

    return boost::geometry::intersects(wayPolygon, object->getPolygon());

}
