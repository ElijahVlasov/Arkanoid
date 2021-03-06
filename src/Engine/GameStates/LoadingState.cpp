#include <Engine/Game.hpp>

#include <Engine/GameStates/LoadingState.hpp>

#include <Utils/SingletonPointer.hpp>

#include <Utils/Graphics/GraphicsManager.hpp>

#include "geometry_defines.hpp"

using namespace Engine;
using namespace Engine::GameStates;



void LoadingState::onActive() {}



void LoadingState::onRemove() {}



void LoadingState::onRender() {

    Utils::Graphics::GraphicsManager::ClearScreen();

    Utils::Graphics::GraphicsManager::DrawTexture(
        GeometryDefines::BoxI(
            GeometryDefines::PointI(0, 0),
            GeometryDefines::PointI(game_->getScreenWidth(), game_->getScreenHeight())
        ),
        *loadingTexture_
    );

    loadingLabel_.draw();

}



void LoadingState::onResize(unsigned int width, unsigned int height) {}



void LoadingState::onKeyDown(int key) {}



void LoadingState::onKeyUp(int key) {}



void LoadingState::onMouseMotion(int x, int y) {}



void LoadingState::onMouseDown(int x, int y, Utils::MouseButton btn) {}



void LoadingState::onMouseUp(int x, int y, Utils::MouseButton btn) {}



void LoadingState::onLoop() {}



Utils::SingletonPointer<Game> LoadingState::getGame() {

    return Utils::SingletonPointer<Game>(Game::getInstance());

}



void LoadingState::setGameState(IGameState* state) {

    game_->setState(state);

}
