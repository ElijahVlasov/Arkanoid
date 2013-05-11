/********************************************

		Интерфейс управления персонажем

********************************************/


#ifndef _CONTROLLER_HPP
#define _CONTROLLER_HPP


namespace Engine {

	class Controller {		

		public:

			virtual bool getLeftState()=0;
			virtual bool getRightState()=0;
			virtual bool getUpState()=0;
			virtual bool getDownState()=0;

	};

}


#endif