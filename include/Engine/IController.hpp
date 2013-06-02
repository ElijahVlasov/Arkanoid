#ifndef _SALT2D_ENGINE_CONTROLLER_HPP
#define _SALT2D_ENGINE_CONTROLLER_HPP


namespace Engine {

	class IController {		

		public:

			virtual bool getLeftState()  = 0;
			virtual bool getRightState() = 0;
			virtual bool getUpState()    = 0;
			virtual bool getDownState()  = 0;

	};

}


#endif