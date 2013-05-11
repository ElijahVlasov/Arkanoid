/*#include <algorithm>
#include <string>

#include <SDL\SDL.h>

#include <Engine\World.hpp>

#include <Utils\Texture.hpp>



using namespace std;


using Engine::World;


using Utils::Texture;


World::World(float x, float y, float width, float height, const string& textureName) {

	// инициализация
	setHeight(height);
	setWidth(width);
	setX(x);
	setY(y);

	// загружаем текстуру мира	
	texture_ = new Texture(textureName);

	// создаем surface мира

}


World::~World() {}


void World::addObject(World::ObjectPointer object) {
	
	auto objIter = find(objects.begin(), objects.end(), object); // ищем объект

	if(objIter != objects.end()) { // если он уже добавлен в список, то выходим
	
		return;

	}

	objects.push_back(object);

}

void World::removeObject(int id) {
	
	auto objI = find_if(objects.begin(), objects.end(), [id](ObjectPointer obj) -> bool {

		if(obj->getId() == id) {
			return true;
		}

	});

	objects.remove(*objI);
}


void World::update() {
	
	for(auto iter = objects.begin(); iter != objects.end(); ++iter) {
		
		(*iter)->onUpdate();

	}

}

void World::draw() {
	
	for(auto iter = objects.begin(); iter != objects.end(); ++iter) {
		
		(*iter)->onRender();

	}

	SDL_GL_SwapBuffers();	

}*/
