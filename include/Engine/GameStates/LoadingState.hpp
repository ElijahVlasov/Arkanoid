#ifndef _SALT2D_ENGINE_GAMESTATES_LOADINGSTATE_HPP
#define _SALT2D_ENGINE_GAMESTATES_LOADINGSTATE_HPP

#include <stdexcept>
#include <thread>

#include <boost/shared_ptr.hpp>

#include <Engine/GameStates/IGameState.hpp>

#include <Utils/LocalizationManager.hpp>
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

                template <class LoadingFunc> LoadingState(LoadingFunc loadingFunc) throw(std::runtime_error);

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

                Utils::SingletonPointer<Game> game_;

                boost::shared_ptr <Utils::Graphics::Texture> loadingTexture_;

                Utils::UI::Label loadingLabel_;

                std::thread loadingThread_;

        };



        template <class LoadingFunc> LoadingState::LoadingState(LoadingFunc loadingFunc) throw(std::runtime_error):
            game_(getGame()),
            loadingThread_(loadingFunc)
        {

            Utils::SingletonPointer <Utils::ResourceManager>     resourceManager     = Utils::ResourceManager::getInstance();
            Utils::SingletonPointer <Utils::LocalizationManager> localizationManager = Utils::LocalizationManager::getInstance();

            loadingTexture_ = resourceManager->getResource<Utils::Graphics::Texture>(LOADING_TEXTURE);

            loadingLabel_.setRect(20, 20, 200, 100);

            loadingLabel_.setText(localizationManager->getString(LOADING_TEXT));

            loadingThread_.detach();

        }

    }

}

#endif
