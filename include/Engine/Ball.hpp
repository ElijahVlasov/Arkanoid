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

            Ball(const GeometryDefines::Point& center, float radius, bool isSleep, float xSpeed = 0.0f, float ySpeed = 0.0f) throw(std::runtime_error);
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

            float getXSpeed() const;
            void setXSpeed(float xSpeed);

            float getYSpeed() const;
            void setYSpeed(float ySpeed);

            GeometryDefines::Box getRect() const;

        private:

            static const float STEP;
            static const std::chrono::milliseconds STEP_TIME;

            std::chrono::system_clock::time_point lastUpdate_;

            bool isSleep_;

            GeometryDefines::Point center_;

            float radius_;

            float xSpeed_, ySpeed_;

    };

}

#endif
