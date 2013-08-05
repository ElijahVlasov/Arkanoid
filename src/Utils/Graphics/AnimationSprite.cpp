#include <mutex>

#include <Utils/Graphics/AnimationSprite.hpp>
#include <Utils/Graphics/GraphicsManager.hpp>
#include <Utils/Graphics/Texture.hpp>

#include "geometry_defines.hpp"

using namespace std;

using namespace Utils;
using namespace Utils::Graphics;



AnimationSprite::AnimationSprite():
    isStarted_(false)
{}



AnimationSprite::~AnimationSprite() {

    stop();

}



void AnimationSprite::addFrame(std::chrono::milliseconds msDuration, const boost::shared_ptr<Texture>& frame) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    Frame newFrame = {msDuration, frame};

    frames_.push_back(newFrame);

}



void AnimationSprite::onRender(const GeometryDefines::Box& box) {

    render();

    std::lock_guard<std::mutex> guard(synchroMutex_);

    GraphicsManager::DrawTexture(box, *frames_.front().texture);

}



void AnimationSprite::onRender(const GeometryDefines::Point& point) {

    render();

    std::lock_guard<std::mutex> guard(synchroMutex_);

    GraphicsManager::DrawTexture(point, *frames_.front().texture);

}



void AnimationSprite::onRender(const GeometryDefines::Polygon& polygon) {

    render();

    std::lock_guard<std::mutex> guard(synchroMutex_);

    GraphicsManager::DrawTexture(polygon, *frames_.front().texture);

}



void AnimationSprite::render() {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    auto now = chrono::system_clock::now();

    if(!isStarted()) {

        start();

    } else {

        if(now - lastTimePoint_ >= frames_.front().msDuration) {

            frames_.push_back(frames_.front());

            frames_.pop_front();

            lastTimePoint_ = now;

        }

    }

}
