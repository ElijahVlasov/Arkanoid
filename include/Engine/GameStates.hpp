#ifndef _SALT2D_ENGINE_GAMESTATES_HPP
#define _SALT2D_ENGINE_GAMESTATES_HPP

#include <Engine/GameStates/IGameState.hpp>
#include <Engine/GameStates/LoadingState.hpp>
#include <Engine/GameStates/MenuState.hpp>
#include <Engine/GameStates/SingleGameState.hpp>
#include <Engine/GameStates/StartLogoState.hpp>

#endif

namespace Engine {

    /** Состояния объекта игры.
      * Все объекты игры должны быть отнаследованы
      * от IGameState.
      * @author Elijah Vlasov
    */

    namespace GameStates {

        class IGameState;
        class LoadingState;
        class MenuState;
        class SingleGameState;
        class StartLogoState;

    }

}
