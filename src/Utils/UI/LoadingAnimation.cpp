#include <chrono>
#include <stdexcept>
#include <string>

#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <boost/mem_fn.hpp>
#include <boost/shared_ptr.hpp>

#include <Utils/Graphics.hpp>
#include <Utils/Resource.hpp>
#include <Utils/ResourceManager.hpp>
#include <Utils/SingletonPointer.hpp>
#include <Utils/Texture.hpp>

#include <Utils/UI/Component.hpp>
#include <Utils/UI/Event.hpp>
#include <Utils/UI/LoadingAnimation.hpp>

#include "salt_defines.h"

using namespace std;

using namespace Utils;
using namespace Utils::UI;



const std::chrono::milliseconds LoadingAnimation::FRAME_DURATION(500);



LoadingAnimation::LoadingAnimation() throw(runtime_error):
    Component()
{

    SingletonPointer <ResourceManager> resourceManager = ResourceManager::getInstance();

    for(size_t i = 0; i < 4; i++) {

        try {

            string fileName = (boost::format("%1%%2%")
                                    % LOADING_ANIMATION_FRAME_PREFIX
                                    % i
                              ).str();

            boost::shared_ptr<Resource> frameResource = resourceManager->getResource(ResourceManager::ResourceType::TEXTURE, fileName);

            frames_.push_back(boost::dynamic_pointer_cast<Texture>(frameResource));

        } catch (const bad_alloc&) {}

    }

    setDrawEvent(boost::bind( boost::mem_fn( &LoadingAnimation::onDraw ), this, _1 ));

}



LoadingAnimation::~LoadingAnimation() {}



void LoadingAnimation::onDraw(Event&) {

    using chrono::system_clock;

    system_clock::time_point now = system_clock::now();

    if( now - lastTimePoint_ >= FRAME_DURATION) {

        frames_.push_back(frames_.front());
        frames_.pop_front();

    }

    lastTimePoint_ = now;

    Graphics::DrawTexture(
        getBoxI(),
        *frames_.front()
    );

}
