#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Engine/Game.hpp>

#include <Engine/GameStates/StartLogoState.hpp>

#include <Utils/ResourceManager.hpp>

#include <Utils/Graphics/GraphicsManager.hpp>
#include <Utils/Graphics/Texture.hpp>

#include "geometry_defines.hpp"

using namespace std;

using namespace GeometryDefines;

using namespace Engine;
using namespace Engine::GameStates;

using namespace Utils;
using namespace Utils::Graphics;



StartLogoState::StartLogoState() throw(runtime_error):
    game_(Game::getInstance()),
    resourceManager_(ResourceManager::getInstance())
{

    logo_ = resourceManager_->getResource<Texture>("textures/logo.png");

}



StartLogoState::~StartLogoState() {

	resourceManager_->deleteResource<Texture>(logo_);

}



void StartLogoState::onActive() {}



void StartLogoState::onRemove() {}



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
