#ifndef _SALT2D_UTILS_UI_LOADINGANIMATION_HPP
#define _SALT2D_UTILS_UI_LOADINGANIMATION_HPP

#include <chrono>
#include <list>
#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Utils/AnimationSprite.hpp>

#include <Utils/UI/Component.hpp>
#include <Utils/UI/Event.hpp>

namespace Utils {

    namespace UI {

        class LoadingAnimation: public Component {

            public:

                LoadingAnimation() throw(std::runtime_error);
                ~LoadingAnimation();

            private:

                void onDraw(Event&);

                static const std::chrono::milliseconds FRAME_DURATION;

                boost::shared_ptr<Sprite> sprite_;

        };

    }

}

#endif
