#include <boost/thread.hpp>

#include <Engine/SaltEngine.hpp>

#include <Utils/Lua.hpp>

using namespace boost;

using namespace Engine;

using Utils::Lua;



SaltEngine::SaltEngine():
	lua_(Lua::getInstance())
{

}



SaltEngine::~SaltEngine() {
	
	lua_->Free();

}



void SaltEngine::run() {


		
}



void SaltEngine::operator() () {
	


}
