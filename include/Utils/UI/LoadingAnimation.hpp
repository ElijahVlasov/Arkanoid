#ifndef _SALT2D_UTILS_UI_LOADINGANIMATION_HPP
#define _SALT2D_UTILS_UI_LOADINGANIMATION_HPP

#include <chrono>
#include <list>
#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Utils/Graphics/AnimationSprite.hpp>

#include <Utils/UI/Component.hpp>
#include <Utils/UI/Event.hpp>

namespace Utils {

    namespace UI {

        class LoadingAnimation: public Component {

            public:

                LoadingAnimation() throw(std::runtime_error);
                ~LoadingAnimation();

            private:

                static void onDraw(Component* sender, Event&);

                static const std::chrono::milliseconds FRAME_DURATION;

                boost::shared_ptr<Graphics::Sprite> sprite_;

        };

    }

}

#endif
