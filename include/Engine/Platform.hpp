#ifndef _SALT2D_ENGINE_PLATFORM_HPP
#define _SALT2D_ENGINE_PLATFORM_HPP

#include <mutex>
#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Engine/Ball.hpp>
#include <Engine/Object.hpp>

#include <Utils/SingletonPointer.hpp>

#include <Utils/Graphics/Texture.hpp>

#include "geometry_defines.hpp"

#define PLATFORM_STEP 10.0f

namespace Engine {

    namespace GameStates {
        class SingleGameState;
    }

    class Platform: public Object {

        public:

            enum MovingDirection {
                RIGHT,
                LEFT
            };

            Platform(const GeometryDefines::Box& rect) throw(std::runtime_error);
            ~Platform();

            void move(MovingDirection dir, float step = PLATFORM_STEP);

            GeometryDefines::Box getRect() const;

            void bindBall(const boost::shared_ptr<Ball>& ball);
            void pushBall();

            boost::shared_ptr<Ball> getBall() const;

        private:

            std::mutex synchroMutex_;

            GeometryDefines::Box rect_;

            boost::shared_ptr<Utils::Graphics::Texture> texture_;

            Utils::SingletonPointer<GameStates::SingleGameState> singleGame_;

            boost::shared_ptr<Ball> ball_;

    };

}

#endif
