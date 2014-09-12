#ifndef _SALT2D_ENGINE_GAMESTATES_LOADINGSTATE_HPP
#define _SALT2D_ENGINE_GAMESTATES_LOADINGSTATE_HPP

#include <chrono>
#include <stdexcept>
#include <thread>

#include <boost/shared_ptr.hpp>

#include <Engine/GameStates/IGameState.hpp>

#include <Utils/Color.hpp>
#include <Utils/ResourceManager.hpp>
#include <Utils/SingletonPointer.hpp>

#include <Utils/Graphics/Texture.hpp>

#include <Utils/UI/Label.hpp>

#include "salt_defines.h"

namespace Engine {

    class Game;

    namespace GameStates {

        class LoadingState: public IGameState {

            public:

                template <class LoadingFunc> LoadingState(LoadingFunc loadingFunc, IGameState* nextState) throw(std::runtime_error);

                void onActive();
                void onRemove();

                void onRender();

                void onResize(unsigned int width, unsigned int height);

                void onKeyDown(int key);
                void onKeyUp(int key);

                void onMouseMotion(int x, int y);
                void onMouseDown(int x, int y, Utils::MouseButton mouseButton);
                void onMouseUp(int x, int y, Utils::MouseButton mouseButton);

                void onLoop();

            private:

                Utils::SingletonPointer<Game> getGame();
                void setGameState(IGameState* state);

                Utils::SingletonPointer<Game> game_;

                boost::shared_ptr <Utils::Graphics::Texture> loadingTexture_;

                Utils::UI::Label loadingLabel_;

                std::thread loadingThread_;

        };



        template <class LoadingFunc> LoadingState::LoadingState(LoadingFunc loadingFunc, IGameState* nextState) throw(std::runtime_error):
            game_(getGame()),
            loadingThread_([loadingFunc, nextState, this]() {
                                    auto startLoading = std::chrono::system_clock::now();

                                    loadingFunc();

                                    auto n = std::chrono::system_clock::now() - startLoading;

                                    while(n <= std::chrono::milliseconds(LOADING_DURATION)) {
                                        n = std::chrono::system_clock::now() - startLoading;
                                    }

                                    this->setGameState(nextState);
                                })
        {

            Utils::SingletonPointer <Utils::ResourceManager>     resourceManager     = Utils::ResourceManager::getInstance();

            Utils::Color color = {1.0f, 1.0f, 0.0f};

            loadingTexture_ = resourceManager->getResource<Utils::Graphics::Texture>(LOADING_TEXTURE);

            loadingLabel_.setRect(20, 20, 200, 100);

            loadingLabel_.setText(LOADING_TEXT);

            loadingLabel_.getFont().setColor(color);
            loadingLabel_.getFont().setSize(18);


            loadingThread_.detach();

        }

    }

}

#endif
