#ifndef _SALT2D_ENGINE_GAMESTATES_STARTLOGOSTATE_HPP
#define _SALT2D_ENGINE_GAMESTATES_STARTLOGOSTATE_HPP

#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Engine/GameStates/IGameState.hpp>

#include <Utils/ResourceManager.hpp>
#include <Utils/Singleton.hpp>
#include <Utils/SingletonPointer.hpp>

#include <Utils/Audio/AudioManager.hpp>
#include <Utils/Audio/Sound.hpp>

#include <Utils/Graphics/Texture.hpp>

namespace Engine {

    class Game;

    namespace GameStates {

        class StartLogoState: public Utils::Singleton<StartLogoState>,
                                     public IGameState {

            SINGLETON(StartLogoState)

            public:

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

            protected:

                StartLogoState() throw(std::runtime_error);
                ~StartLogoState();

            private:

                Utils::SingletonPointer<Game> game_;

                Utils::SingletonPointer<Utils::Audio::AudioManager>    audioManager_;
                Utils::SingletonPointer<Utils::ResourceManager> resourceManager_;

                boost::shared_ptr<Utils::Audio::Sound>       hello_;
                boost::shared_ptr<Utils::Audio::SoundPlayer> helloPlayer_;

                boost::shared_ptr<Utils::Graphics::Texture> logo_;

        };

    }

}

#endif
