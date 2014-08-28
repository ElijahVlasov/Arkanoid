#ifndef _SALT2D_ENGINE_BALL_HPP
#define _SALT2D_ENGINE_BALL_HPP

#include <chrono>
#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Engine/Object.hpp>

#include <Utils/Graphics/Texture.hpp>

#include "geometry_defines.hpp"

namespace Engine {

    class Ball: public Object {

        public:

            Ball(const GeometryDefines::Point& center, float radius, bool isSleep,
                    float speed = 300.0f, const GeometryDefines::Vector2D& direction = GeometryDefines::Vector2D(0.0f, 0.0f)) throw(std::runtime_error);
            ~Ball();

            void move(float x, float y);

            void update();

            void sleep();
            void awake();

            bool isSleep() const;

            const GeometryDefines::Point& getCenter() const;
            void setCenter(const GeometryDefines::Point& center);
            void setCenter(float x, float y);

            float getRadius() const;
            void setRadius(float radius);

            float getAngle() const;
            void setAngle(float angle);

            void rotate(float angle);

            void setDirection(const GeometryDefines::Vector2D& direction);
            const GeometryDefines::Vector2D& getDirection() const;

            float getSpeed() const;
            void setSpeed(float speed);

            GeometryDefines::Point getNextPoint() const;

            GeometryDefines::Box getRect() const;

        private:

            static const std::chrono::milliseconds STEP_TIME;

            std::chrono::system_clock::time_point lastUpdate_;

            bool isSleep_;

            GeometryDefines::Point center_;

            float radius_;

            float speed_;

            GeometryDefines::Vector2D direction_;

    };

}

#endif
