#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/assert.hpp>
#include <Utils/ResourceManager.hpp>
#include <Utils/SingletonPointer.hpp>

#include <Utils/Graphics/GraphicsManager.hpp>
#include <Utils/Graphics/Texture.hpp>

#include <Utils/UI/Picture.hpp>

using namespace std;

using namespace Utils;
using namespace Utils::Graphics;
using namespace Utils::UI;



Picture::Picture() throw(runtime_error):
    Component()
{}



Picture::Picture(const char* textureName) throw(runtime_error, invalid_argument):
    Component()
{

    ASSERT(
        (textureName != 0),
        invalid_argument("textureName")
    );

    texture_ = loadTexture(string(textureName));

    setDrawEvent( &Picture::onDraw );

}



Picture::Picture(const string& textureName) throw(invalid_argument, runtime_error):
    Component(),
    texture_(loadTexture(textureName))
{

    setDrawEvent( &Picture::onDraw );

}



Picture::Picture(const boost::shared_ptr<Texture>& texture) throw(runtime_error):
    Component(),
    texture_(texture)
{

    setDrawEvent( &Picture::onDraw );

}



Picture::~Picture() {}



boost::shared_ptr<Texture> Picture::getTexture() const {

    return texture_;

}



void Picture::setTexture(const boost::shared_ptr<Texture>& texture) {

    texture_ = texture;

}



boost::shared_ptr<Texture> Picture::loadTexture(const std::string& textureName) throw(invalid_argument, runtime_error) {

    SingletonPointer<ResourceManager> resourceManager = ResourceManager::getInstance();

    return resourceManager->getResource<Texture>(textureName);

}



void Picture::onDraw(Component* sender, Event& event) {

    Picture* pic = dynamic_cast<Picture*>(sender);

    GraphicsManager::DrawTexture(pic->getBoxI(), *pic->texture_);

}
