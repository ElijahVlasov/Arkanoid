#ifndef _SALT2D_ENGINE_ICAMERAUPDATER_HPP
#define _SALT2D_ENGINE_ICAMERAUPDATER_HPP

#include <Engine/Camera.hpp>

namespace Engine {

    /** Интерфейс классов, обновляющих
      * камеру.
      * @author Elijah Vlasov
    */

    class ICameraUpdater {
    
        public:
        
            /** Обновить камеру.
              * @param camera камера 
            */
        
            virtual void updateCamera(Camera& camera)=0;
    
    };

}

#endif