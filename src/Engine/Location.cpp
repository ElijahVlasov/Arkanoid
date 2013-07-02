#include <list>
#include <string>
#include <stdexcept>

#include <boost/intrusive_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <Engine/Location.hpp>
#include <Engine/LocationLayer.hpp>

#include <Utils/Resource.hpp>
#include <Utils/ResourceManager.hpp>
#include <Utils/Texture.hpp>

#include "World.pb.h"

using namespace std;

using namespace Engine;

using namespace Utils;



Location::Location() {}



Location::Location(const EngineData::Location& locationData) throw(runtime_error):
	width_(locationData.width()),
	height_(locationData.height()),
	name_(locationData.name())
{

	try {

		boost::intrusive_ptr<ResourceManager> resourceManager(ResourceManager::getInstance(), false);

		boost::shared_ptr<Resource> textureResource = resourceManager->getResource(ResourceManager::ResourceType::TEXTURE, locationData.ground_texture());

		groundTexture_ = boost::dynamic_pointer_cast<Texture>(textureResource);

	} catch (const bad_cast&) {}

}



Location::~Location() {}



void Location::setGroundTexture(const boost::shared_ptr<Texture>& groundTexture) {

	groundTexture_ = groundTexture;

}



boost::shared_ptr<Texture> Location::getGroundTexture() const {

	return groundTexture_;

}



void Location::addLayer(const LocationLayerPtr& layer) {

	layers_.push_back(layer);

}



void Location::setLayers(const list<LocationLayerPtr>& layers) {

	layers_ = layers;

}



const list<LocationLayerPtr>& Location::getLayers() const {

	return layers_;

}



void Location::setWidth(float width) {

	width_ = width;

}



float Location::getWidth() const {

	return width_;

}



void Location::setHeight(float height) {

	height_ = height;

}



float Location::getHeight() const {

	return height_;

}



void Location::setName(const char* name) {

	if(name == 0) {
		name_ = "";
	} else {
		name_ = name;
	}

}



void Location::setName(const string& name) {

	name_ = name;

}



string Location::getName() const {

	return name_;

}
