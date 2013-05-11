#include <stdexcept>

#include <boost/geometry/geometries/point_xy.hpp>

#include <Utils.hpp>

#include <Utils/UI/Label.hpp>

using namespace std;

using namespace boost::geometry::model::d2;

using namespace Utils;
using namespace Utils::FreeType;
using namespace Utils::UI;



Label::Label() throw(runtime_error):
	Component()
{}



Label::~Label() {}



void Label::draw() {

	drawText();

	Component::draw();

}



void Label::drawText() {

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

	float textWidth		=	text.getWidth();
	float textHeight	=	text.getHeight();

	// если текст больше Label'а, то "обрезаем" его:

	if(textWidth > width) {

		textWidth = width;

	}

	if(textHeight > height) {
	
		textHeight = height;

	}

	::draw(
		x,
		y,
		textWidth,
		textHeight,
		coordArray,
		text
	);

}
