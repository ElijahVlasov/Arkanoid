#include <stdexcept>

#include <boost/geometry/geometries/point_xy.hpp>

#include <Engine/Game.hpp>

#include <Engine/GameStates/StartLogoState.hpp>

#include <Utils.hpp>

using namespace std;

using namespace boost::geometry::model::d2;

using namespace Engine;
using namespace Engine::GameStates;

using namespace Utils;



StartLogoState::StartLogoState() throw(runtime_error):
    game_(Game::getInstance()),
    logo_("logo.png")
{}



void StartLogoState::onRender() {

    static const CoordArray coords = {
        point_xy<float>(0.0f, 0.0f),
        point_xy<float>(1.0f, 0.0f),
        point_xy<float>(0.0f, 1.0f),
        point_xy<float>(1.0f, 1.0f)
    };

    draw(
        0.0f, 0.0f,
        game_->getScreenWidth(),
        game_->getScreenHeight(),
        coords,
        logo_
    );

}



void StartLogoState::onResize(unsigned int width, unsigned int height) {}



void StartLogoState::onKeyDown(int key) {}



void StartLogoState::onKeyUp(int key) {}



void StartLogoState::onMouseMotion(int x, int y) {}



void StartLogoState::onMouseDown(int x, int y, Utils::MouseButton btn) {}



void StartLogoState::onMouseUp(int x, int y, Utils::MouseButton btn) {}
