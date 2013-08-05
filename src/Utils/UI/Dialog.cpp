#include <Utils/Graphics/GraphicsManager.hpp>

#include <Utils/UI/Dialog.hpp>

using namespace Utils;
using namespace Utils::Graphics;
using namespace Utils::UI;



Dialog::Dialog():
    Container()
{}



Dialog::~Dialog() {}



void Dialog::drawSelf() {

    GraphicsManager::DrawTexture(
        getBoxI(),
        *frame_
    );

}
