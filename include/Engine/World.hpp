#ifndef _WORLD_HPP
#define _WORLD_HPP

#include <SDL\SDL.h>

#include <list>
#include <memory>
#include <string>
#include <stdexcept>

#include <Engine\Object.hpp>


using namespace std;

namespace Engine {

	class World: public Object {

		public:

			typedef shared_ptr<Object> ObjectPointer;
	
		private:

			list<ObjectPointer> objects;

			SDL_Surface* worldSurface;

		public: 

			World(float x, float y, float width, float height, const string& textureName) throw(runtime_error);
			~World();

			void addObject(ObjectPointer object);
			void removeObject(int id);

			void update();
			void draw();

	};

}


#endif