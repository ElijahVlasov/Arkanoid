#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Engine/Game.hpp>

#include <Engine/GameStates/StartLogoState.hpp>

#include <Utils/ResourceManager.hpp>

#include <Utils/Audio/AudioManager.hpp>
#include <Utils/Audio/Sound.hpp>
#include <Utils/Audio/SoundPlayer.hpp>

#include <Utils/Graphics/GraphicsManager.hpp>
#include <Utils/Graphics/Texture.hpp>

#include "geometry_defines.hpp"

using namespace std;

using namespace GeometryDefines;

using namespace Engine;
using namespace Engine::GameStates;

using namespace Utils;
using namespace Utils::Audio;
using namespace Utils::Graphics;



StartLogoState::StartLogoState() throw(runtime_error):
    audioManager_(AudioManager::getInstance()),
    game_(Game::getInstance()),
    resourceManager_(ResourceManager::getInstance())
{

    hello_ = resourceManager_->getResource<Sound>("sounds/hello.ogg");
    logo_  = resourceManager_->getResource<Texture>("textures/logo.png");

    helloPlayer_ = boost::shared_ptr<SoundPlayer>(audioManager_->createSoundPlayer(hello_));

}



StartLogoState::~StartLogoState() {

    resourceManager_->deleteResource<Sound>(hello_);
	resourceManager_->deleteResource<Texture>(logo_);

}



void StartLogoState::onActive() {

    helloPlayer_->play();

}



void StartLogoState::onRemove() {

    helloPlayer_->stop();

}



void StartLogoState::onRender() {

    GraphicsManager::ClearScreen();

    GraphicsManager::DrawTexture(
        BoxI( PointI(0, 0),
              PointI( game_->getScreenWidth(), game_->getScreenHeight() )
        ),
        *logo_
    );

}



void StartLogoState::onResize(unsigned int width, unsigned int height) {}



void StartLogoState::onKeyDown(int key) {}



void StartLogoState::onKeyUp(int key) {}



void StartLogoState::onMouseMotion(int x, int y) {}



void StartLogoState::onMouseDown(int x, int y, Utils::MouseButton btn) {}



void StartLogoState::onMouseUp(int x, int y, Utils::MouseButton btn) {}
