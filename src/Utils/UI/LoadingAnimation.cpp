#include <chrono>
#include <stdexcept>
#include <string>

#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <boost/mem_fn.hpp>
#include <boost/shared_ptr.hpp>

#include <Utils/Graphics.hpp>
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


        string fileName = (boost::format("%1%%2%.png")
                                    % LOADING_ANIMATION_FRAME_PREFIX
                                    % i
                              ).str();

        animationSprite->addFrame(FRAME_DURATION, resourceManager->getResource<Texture>(fileName));

    }

    setDrawEvent( &LoadingAnimation::onDraw );

}



LoadingAnimation::~LoadingAnimation() {}



void LoadingAnimation::onDraw(Component* sender, Event&) {

    auto loadingAnimationSender = dynamic_cast<LoadingAnimation*>(sender);

    loadingAnimationSender->sprite_->onRender(loadingAnimationSender->getBoxI());

}
