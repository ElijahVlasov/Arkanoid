#ifndef _SALT2D_ENGINE_BALL_HPP
#define _SALT2D_ENGINE_BALL_HPP

#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Utils/Graphics/Texture.hpp>

#include "geometry_defines.hpp"

namespace Engine {

    class Ball {

        public:

            Ball(const GeometryDefines::Point& center, float radius, bool isSleep, float xSpeed = 0.0f, float ySpeed = 0.0f) throw(std::runtime_error);

            void move(float x, float y);

            void update();

            void draw();

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

        private:

            static const float STEP;

            bool isSleep_;

            boost::shared_ptr<Utils::Graphics::Texture> texture_;

            GeometryDefines::Point center_;

            float radius_;

            float xSpeed_, ySpeed_;

    };

}

#endif
