#include <Utils/Graphics.hpp>

#include <Utils/UI/Dialog.hpp>

using namespace Utils;

using namespace Utils::UI;

Dialog::Dialog():
    Container()
{}



Dialog::~Dialog() {}



void Dialog::drawSelf() {

    Graphics::DrawTexture(
        getBoxI(),
        *frame_
    );

}
