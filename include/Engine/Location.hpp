#ifndef _SALT2D_ENGINE_LOCATION_HPP
#define _SALT2D_ENGINE_LOCATION_HPP

#include <list>
#include <string>
#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Utils/Texture.hpp>

#include "World.pb.h"

namespace Engine {

	class LocationLayer;

	typedef boost::shared_ptr<LocationLayer> LocationLayerPtr;

	class Location {

		public:

			Location();
			Location(const EngineDate::Location& locationData) throw(std::runtime_error);

			~Location();

			void setGroundTexture(const boost::shared_ptr<Utils::Texture>& groundTexture);
			boost::shared_ptr<Utils::Texture> getGroundTexture() const;

			void addLayer(const LocationLayerPtr& layer);
			void setLayers(const std::list<LocationLayerPtr>& layers);
			const std::list<LocationLayerPtr>& getLayers() const;

			void setWidth(float width);
			float getWidth() const;

			void setHeight(float height);
			float getHeight() const;

			void setName(const char* name);
			void setName(const std::string& name);
			std::string getName() const;

		private:

			float width_, height_;

			std::string name_;

			boost::shared_ptr<Utils::Texture> groundTexture_;

			std::list<LocationLayerPtr> layers_;

	};

}

#endif
