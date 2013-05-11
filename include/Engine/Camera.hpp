#ifndef _SALT2D_ENGINE_CAMERA_HPP
#define _SALT2D_ENGINE_CAMERA_HPP

#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Engine/IUpdatable.hpp>

namespace Engine {

	class Camera {
	
		public:

			Camera(IUpdatable* updatable)	throw(std::invalid_argument);
			Camera(const boost::shared_ptr<IUpdatable>& updatable) 
											throw(std::invalid_argument);

			~Camera();

			void setUpdate(IUpdatable* updatable)
											throw(std::invalid_argument);

			void setUpdate(const boost::shared_ptr<IUpdatable>& updatable)
											throw(std::invalid_argument);

		private:

			boost::shared_ptr<IUpdatable> updatable;

	};

}

#endif