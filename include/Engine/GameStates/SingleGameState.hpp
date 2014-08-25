#ifndef _SALT2D_ENGINE_GAMESTATES_SINGLEGAMESTATE_HPP
#define _SALT2D_ENGINE_GAMESTATES_SINGLEGAMESTATE_HPP

#include <chrono>
#include <stdexcept>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <Engine/Ball.hpp>
#include <Engine/Block.hpp>
#include <Engine/Platform.hpp>

#include <Engine/GameStates/IGameState.hpp>
#include <Engine/GameStates/MenuState.hpp>

#include <Utils/Lua.hpp>
#include <Utils/Singleton.hpp>
#include <Utils/SingletonPointer.hpp>

#include <Utils/Audio/AudioManager.hpp>
#include <Utils/Audio/Sound.hpp>
#include <Utils/Audio/SoundPlayer.hpp>

#include <Utils/Graphics/Texture.hpp>

namespace Engine {

    class Game;

    namespace GameStates {

        class SingleGameState: public Utils::Singleton<SingleGameState>,
                                    public IGameState {

            SINGLETON(SingleGameState)

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

                void init() throw(std::runtime_error);
                void quit();

                float getWorldWidth()  const;
                float getWorldHeight() const;

            protected:

                SingleGameState() throw(std::runtime_error);

            private:

                void checkBallAndWalls();
                void checkBallAndObjects();

                void die();

                void bounceSound();

                static const std::chrono::milliseconds LOADING_DURATION;

                void showDebugInfo();
                void makeScreenshot();

                Utils::SingletonPointer<Engine::Game>                   game_;

                Utils::SingletonPointer<Utils::Lua>        	            lua_;

                Utils::SingletonPointer<MenuState>                      menuState_;

                Utils::SingletonPointer<Utils::Audio::AudioManager>     audioManager_;

                boost::shared_ptr<Utils::Graphics::Texture>     background_;
                boost::shared_ptr<Utils::Audio::Sound>          music_;
                boost::shared_ptr<Utils::Audio::Sound>          bounceSound_;

                boost::shared_ptr<Utils::Audio::SoundPlayer>    musicPlayer_;

                boost::shared_ptr<Engine::Platform>             platform_;

                bool isPlatformClicked_;
                int  lastMouseX_;
                std::vector< std::vector< boost::shared_ptr<Block> > > blocks_;
                boost::shared_ptr<Ball>  ball_;

        };

    }

}

#endif
