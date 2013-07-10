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
    Component(),
    sprite_(new AnimationSprite())
{

    SingletonPointer <ResourceManager> resourceManager = ResourceManager::getInstance();

    boost::shared_ptr<AnimationSprite> animationSprite = boost::dynamic_pointer_cast<AnimationSprite>(sprite_);

    for(size_t i = 0; i < 4; i++) {

        try {

            string fileName = (boost::format("%1%%2%")
                                    % LOADING_ANIMATION_FRAME_PREFIX
                                    % i
                              ).str();

            boost::shared_ptr<Resource> frameResource = resourceManager->getResource(ResourceManager::ResourceType::TEXTURE, fileName);

            animationSprite->addFrame(FRAME_DURATION, boost::dynamic_pointer_cast<Texture>(frameResource));

        } catch (const bad_alloc&) {}

    }

    setDrawEvent(boost::bind( boost::mem_fn( &LoadingAnimation::onDraw ), this, _1 ));

}



LoadingAnimation::~LoadingAnimation() {}



void LoadingAnimation::onDraw(Event&) {

    sprite_->onRender(getBoxI());

}
