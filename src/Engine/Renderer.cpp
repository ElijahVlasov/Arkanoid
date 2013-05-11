#include "config.h"

#ifdef MS_WINDOWS
#include <Windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include <stdexcept>

#include <boost/geometry.hpp>

#include <Engine/Game.hpp>
#include <Engine/Renderer.hpp>

#include <Utils.hpp>

using namespace std;

using namespace Engine;
using namespace boost::geometry;
using model::d2::point_xy;



Renderer::Renderer() throw(runtime_error):
	game_(Game::getInstance())
{

	initGL(game_->getScreenWidth(), game_->getScreenHeight());

}



Renderer::~Renderer() {

	if(game_ != 0) {
		game_->Free();
	}

}



void Renderer::initGL(unsigned int scrWidth, unsigned int scrHeight) {

	//glViewport(0, 0, scrWidth, scrHeight);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, scrWidth, 0, scrHeight);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}



void Renderer::onResize(unsigned int scrWidth, unsigned int scrHeight) {

	gluOrtho2D(0, scrWidth, 0, scrHeight);

}



void Renderer::onRender() {
}
