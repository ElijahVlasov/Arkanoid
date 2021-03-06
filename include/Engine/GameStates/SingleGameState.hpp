#ifndef _SALT2D_ENGINE_GAMESTATES_SINGLEGAMESTATE_HPP
#define _SALT2D_ENGINE_GAMESTATES_SINGLEGAMESTATE_HPP

#include <chrono>
#include <stdexcept>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <Engine/Ball.hpp>
#include <Engine/Block.hpp>
#include <Engine/DebugOutput.hpp>
#include <Engine/Level.hpp>
#include <Engine/LevelManager.hpp>
#include <Engine/Platform.hpp>

#include <Engine/GameStates/LoadingState.hpp>

#include <Engine/GameStates/IGameState.hpp>
#include <Engine/GameStates/MenuState.hpp>

#include <Utils/Lua.hpp>
#include <Utils/Singleton.hpp>
#include <Utils/SingletonPointer.hpp>

#include <Utils/Audio/AudioManager.hpp>
#include <Utils/Audio/Sound.hpp>
#include <Utils/Audio/SoundPlayer.hpp>

#include <Utils/FreeType/Font.hpp>

#include <Utils/Graphics/Texture.hpp>

#include "geometry_defines.hpp"

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

                static float genAngleDelta();

                void checkBallAndWalls();
                void checkBallAndObjects();
                void checkBallAndPlatform();
                void checkBallAndBlocks();

                void die();

                void bounceSound();

                void printDebugInfo();

                void makeScreenshot();

                boost::shared_ptr<LoadingState> loadingState_;

                Utils::SingletonPointer<Engine::Game>                   game_;

                Utils::SingletonPointer<Utils::Lua>        	            lua_;

                Utils::SingletonPointer<MenuState>                      menuState_;

                Utils::SingletonPointer<Utils::Audio::AudioManager>     audioManager_;

                boost::shared_ptr<DebugOutput> debugOutput_;

                boost::shared_ptr<Utils::FreeType::Font> loseFont_;
                boost::shared_ptr<Utils::FreeType::Font> winFont_;

                boost::shared_ptr<Utils::Graphics::Texture>     bar_;
                boost::shared_ptr<Utils::Graphics::Texture>     ballIcon_;

                boost::shared_ptr<Utils::Audio::Sound>          bounceSound_;

                boost::shared_ptr<Utils::Audio::SoundPlayer>    musicPlayer_;

                boost::shared_ptr<Engine::Platform>             platform_;

                bool isPlatformClicked_;
                int  lastMouseX_;

                boost::shared_ptr<LevelManager> levelManager_;

                boost::shared_ptr<Level> level_;

                boost::shared_ptr<Ball>  ball_;


                bool isWin_;

                bool isPaused_;

                unsigned int ballsCount_;

        };

    }

}

#endif
