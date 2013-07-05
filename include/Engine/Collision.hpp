#ifndef _SALT2D_ENGINE_COLLISION_HPP
#define _SALT2D_ENGINE_COLLISION_HPP

#include <Engine/Object.hpp>

namespace Engine {

    /** Столкновение. Хранит все данные о столкновении.
      * @author Elijah Vlasov
    */

    class Collision {

        public:

            /** Конструктор.
              * @param recipient Объект, которому посылается столкновение.
              * @param sender Объект, столкнувшийся с первым.
            */

            inline Collision(const ObjectPtr& recipient, const ObjectPtr& sender):
                recipient_(recipient),
                sender_(sender)
            {}



            /** Получить объект-получатель.
            */

            inline const ObjectPtr& getRecipient() const {
                return recipient_;
            }



            /** Получить объект-отправитель.
            */

            inline const ObjectPtr& getSender() const {
                return sender_;
            }

        private:

            ObjectPtr recipient_, sender_;

    };

}

#endif
