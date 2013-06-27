#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Engine/Game.hpp>

#include <Engine/GameStates/StartLogoState.hpp>

#include <Utils/Graphics.hpp>
#include <Utils/ResourceManager.hpp>
#include <Utils/Texture.hpp>

#include "geometry_defines.hpp"

using namespace std;

using namespace GeometryDefines;

using namespace Engine;
using namespace Engine::GameStates;

using namespace Utils;



StartLogoState::StartLogoState() throw(runtime_error):
    game_(Game::getInstance(), false),
    resourceManager_(ResourceManager::getInstance(), false)
{

    try {

        boost::shared_ptr<Resource> textureResource = resourceManager_->getResource(ResourceManager::ResourceType::TEXTURE, "textures/logo.png");

        logo_ = boost::dynamic_pointer_cast<Texture>(textureResource);

    } catch(const bad_cast&) {}

}



void StartLogoState::onRender() {

    Graphics::ClearScreen();

    Graphics::DrawTexture(
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
