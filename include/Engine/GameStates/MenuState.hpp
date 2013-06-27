#ifndef _SALT2D_ENGINE_GAMESTATES_MENUSTATE_HPP
#define _SALT2D_ENGINE_GAMESTATES_MENUSTATE_HPP

#include <mutex>
#include <stdexcept>

#include <boost/intrusive_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <Engine/GameStates/IGameState.hpp>

#include <Utils/Singleton.hpp>

#include <Utils/UI/Menu.hpp>

namespace Engine {

    class Game;

    namespace GameStates {

        class MenuState: public Utils::Singleton<MenuState>, public IGameState {

            SINGLETON(MenuState)

            public:

                void setMenu(const boost::shared_ptr<Utils::UI::Menu>& menu);
                const boost::shared_ptr<Utils::UI::Menu>& getMenu() const;

                void onRender();

                void onResize(unsigned int width, unsigned int height);

                void onKeyDown(int key);
                void onKeyUp(int key);

                void onMouseMotion(int x, int y);
                void onMouseDown(int x, int y, Utils::MouseButton mouseButton);
                void onMouseUp(int x, int y, Utils::MouseButton mouseButton);

            protected:

                MenuState() throw(std::runtime_error);

            private:

                mutable std::mutex synchroMutex_;

                boost::intrusive_ptr<Engine::Game> game_;

                boost::shared_ptr<Utils::UI::Menu> menu_;

        };

    }

}

#endif
