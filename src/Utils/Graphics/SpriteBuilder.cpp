#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <tinyxml.h>

#include <Utils/assert.hpp>
#include <Utils/ResourceManager.hpp>
#include <Utils/SingletonPointer.hpp>

#include <Utils/Graphics/AnimationSprite.hpp>
#include <Utils/Graphics/Sprite.hpp>
#include <Utils/Graphics/SpriteBuilder.hpp>
#include <Utils/Graphics/StaticSprite.hpp>
#include <Utils/Graphics/Texture.hpp>

using namespace std;

using namespace Utils;
using namespace Utils::Graphics;

const string SpriteBuilder::SPRITE_ROOT_ELEMENT = "sprite";



SpriteBuilder::SpriteBuilder():
    resourceManager_(ResourceManager::getInstance())
{}



boost::shared_ptr<Sprite> SpriteBuilder::createSprite(const char* fileName, SpriteBuilder::SpriteType spriteType) throw(invalid_argument, runtime_error) {

    ASSERT(
        (fileName != 0),
        invalid_argument("fileName")
    );

    return createSprite(string(fileName), spriteType);

}



boost::shared_ptr<Sprite> SpriteBuilder::createSprite(const string& fileName, SpriteBuilder::SpriteType spriteType) throw(invalid_argument, runtime_error) {

    ASSERT(
        !fileName.empty(),
        invalid_argument("fileName")
    );

    switch(spriteType) {

        case STATIC: {
            return instance_->createStaticSprite(fileName);
        }
        break;

        case ANIMATION: {
            return instance_->createAnimationSprite(fileName);
        }
        break;

    }

}



boost::shared_ptr<Sprite> SpriteBuilder::createStaticSprite(const string& fileName) throw(runtime_error) {

    boost::shared_ptr<Texture>      texture = resourceManager_->getResource<Texture>(fileName);

    boost::shared_ptr<StaticSprite> sprite(new StaticSprite(texture));

    return sprite;

}



boost::shared_ptr<Sprite> SpriteBuilder::createAnimationSprite(const std::string& fileName) throw(runtime_error) {

    boost::shared_ptr<AnimationSprite> animationSprite(new AnimationSprite());

    string xmlSprite = resourceManager_->getFileData(fileName);

    TiXmlDocument doc;

    doc.Parse(xmlSprite.c_str());

    ASSERT(
        !doc.Error(),
        runtime_error(doc.ErrorDesc())
    );

    TiXmlElement* rootElement = doc.RootElement();

    ASSERT(
        (rootElement != 0),
        runtime_error("Document hasn't root element")
    );

    ASSERT(
        (rootElement->ValueStr() == SPRITE_ROOT_ELEMENT),
        runtime_error("Unknown document type")
    );

    for(TiXmlNode* node = rootElement->FirstChild(); node != 0; node = node->NextSibling()) {

        TiXmlElement* frame = node->ToElement();

        int frameDuration;
        string textureName;

        if(frame == 0) {
            continue;
        }

        int err = frame->QueryIntAttribute("duration", &frameDuration);

        ASSERT(
            (err != TIXML_WRONG_TYPE),
            runtime_error("Frame attribute \"duration\" has wrong type")
        );

        if(err == TIXML_NO_ATTRIBUTE) {
            frameDuration = 300;
        }

        err = frame->QueryStringAttribute("texture", &textureName);

        ASSERT(
            (err != TIXML_WRONG_TYPE),
            runtime_error("Frame attribute \"texture\" has wrong type")
        );

        ASSERT(
            (err != TIXML_NO_ATTRIBUTE),
            runtime_error("Frame hasn't attribute \"texture\"")
        );

        boost::shared_ptr<Texture> texture = resourceManager_->getResource<Texture>(textureName);

        animationSprite->addFrame(chrono::milliseconds(frameDuration), texture);

    }

    return animationSprite;

}
