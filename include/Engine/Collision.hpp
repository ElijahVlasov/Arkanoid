#ifndef _SALT2D_ENGINE_COLLISION_HPP
#define _SALT2D_ENGINE_COLLISION_HPP

#include <Engine/Object.hpp>

namespace Engine {

    /** ������������. ������ ��� ������ � ������������.
      * @author Elijah Vlasov
    */

    class Collision {

        public:

            /** �����������.
              * @param recipient ������, �������� ���������� ������������.
              * @param sender ������, ������������� � ������.
            */

            inline Collision(const ObjectPtr& recipient, const ObjectPtr& sender):
                recipient_(recipient),
                sender_(sender)
            {}



            /** �������� ������-����������.
            */

            inline const ObjectPtr& getRecipient() const {
                return recipient_;
            }



            /** �������� ������-�����������.
            */

            inline const ObjectPtr& getSender() const {
                return sender_;
            }

        private:

            ObjectPtr recipient_, sender_;

    };

}

#endif
