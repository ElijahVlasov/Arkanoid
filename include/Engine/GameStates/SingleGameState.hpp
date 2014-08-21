#ifndef _SALT2D_ENGINE_GAMESTATES_SINGLEGAMESTATE_HPP
#define _SALT2D_ENGINE_GAMESTATES_SINGLEGAMESTATE_HPP

#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Engine/GameStates/IGameState.hpp>
#include <Engine/GameStates/MenuState.hpp>

#include <Utils/Lua.hpp>
#include <Utils/Singleton.hpp>
#include <Utils/SingletonPointer.hpp>

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

                void quit();

                void onActive();
                void onRemove();

                void onRender();

                void onResize(unsigned int width, unsigned int height);

                void onKeyDown(int key);
                void onKeyUp(int key);

                void onMouseMotion(int x, int y);
                void onMouseDown(int x, int y, Utils::MouseButton mouseButton);
                void onMouseUp(int x, int y, Utils::MouseButton mouseButton);

                void init() throw(std::runtime_error);

            protected:

                SingleGameState() throw(std::runtime_error);

            private:

                void showDebugInfo();
                void makeScreenshot();

                Utils::SingletonPointer<Engine::Game>           game_;

                Utils::SingletonPointer<Utils::Lua>        	    lua_;

                Utils::SingletonPointer<MenuState>              menuState_;

                boost::shared_ptr<Utils::Graphics::Texture>     background_;
                boost::shared_ptr<Utils::Audio::Sound>          music_;

                boost::shared_ptr<Utils::Audio::SoundPlayer>    musicPlayer_;

        };

    }

}

#endif
