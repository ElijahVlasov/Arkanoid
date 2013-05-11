#include <cmath>

#include <stdexcept>
#include <string>

#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/function.hpp>

#include <Utils.hpp>

using namespace std;

using namespace boost::geometry::model::d2;

using namespace Utils;

using namespace Utils::UI;



Button::Button() throw(runtime_error):
	Component()
{
}



Button::~Button() {}



void Button::draw() {

	drawTexture();
	drawText();

	Component::draw();

}



void Button::drawTexture() {

	CoordArray coordArray = {
		point_xy<float>(0.0f, 0.0f),
		point_xy<float>(1.0f, 0.0f),
		point_xy<float>(0.0f, 1.0f),
		point_xy<float>(1.0f, 1.0f)
	};

	float x			=	static_cast<float>(getX());
	float y			=	static_cast<float>(getY());
	float width		=	static_cast<float>(getWidth());
	float height		=	static_cast<float>(getHeight());

	::draw(
		x,
		y,
		width,
		height,
		coordArray,
		curTexture_
	);

}



void Button::drawText() {

	CoordArray coordArray = {
		point_xy<float>(0.0f, 0.0f),
		point_xy<float>(1.0f, 0.0f),
		point_xy<float>(0.0f, 1.0f),
		point_xy<float>(1.0f, 1.0f)
	};

	float x			=	static_cast<float>(getX());
	float y			=	static_cast<float>(getY());
	float width		=	static_cast<float>(getWidth());
	float height	=	static_cast<float>(getHeight());

	Texture text;

	// рендерим текст
	try {

		text = getFont().renderText(getText());

	} catch(const invalid_argument&) {

	} catch(const runtime_error&) {

	}


	float textWidth		=	static_cast<float>(text.getWidth());
	float textHeight	=	static_cast<float>(text.getHeight());

	float textX, textY;

	// получаем величину отступа от края кнопки
	textX = abs(width	-	textWidth)	/ 2;
	textY = abs(height	-	textHeight)	/ 2;

	if(textWidth >= width) { 
	
		textX = x - textX; // текст выходит за край кнопки

	} else {
	
		textX = x + textX; // не выходит

	}

	// аналогично
	if(textHeight >= height) {
	
		textY = y - textY;

	} else {
	
		textY = y + textY;

	}

	::draw(
		textX,
		textY,
		textWidth,
		textHeight,
		coordArray,
		text
	);

}



void Button::mouseDown(int x, int y, Utils::MouseButton btn) {

	curTexture_ = clickedTexture_;

	Component::mouseDown(x, y, btn);

}



void Button::mouseUp(int x, int y, Utils::MouseButton btn) {

	curTexture_ = defTexture_;

	Component::mouseUp(x, y, btn);

}
