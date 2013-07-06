#ifndef _SALT2D_UTILS_UI_LOADINGANIMATION_HPP
#define _SALT2D_UTILS_UI_LOADINGANIMATION_HPP

#include <chrono>
#include <list>
#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Utils/Texture.hpp>

#include <Utils/UI/Component.hpp>
#include <Utils/UI/Event.hpp>

namespace Utils {

    namespace UI {

        class LoadingAnimation: public Component {

            public:

                LoadingAnimation() throw(std::runtime_error);
                ~LoadingAnimation();

            private:

                static const std::chrono::milliseconds FRAME_DURATION;

                std::chrono::system_clock::time_point lastTimePoint_;

                void onDraw(Event&);

                std::list< boost::shared_ptr<Texture> > frames_;

        };

    }

}

#endif
