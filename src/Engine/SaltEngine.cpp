#include <list>
#include <thread>

#include <boost/foreach.hpp>
#include <boost/mem_fn.hpp>
#include <boost/shared_ptr.hpp>

#include <Engine/SaltEngine.hpp>

#include <Utils/Lua.hpp>

using namespace std;

using namespace Engine;

using Utils::Lua;



SaltEngine::SaltEngine():
    lua_(Lua::getInstance(), false)
{

}



SaltEngine::~SaltEngine() {}



void SaltEngine::run() {

    engineThread_ = boost::shared_ptr<std::thread>(new std::thread(boost::mem_fn(&SaltEngine::engineLoop), this) );

}



void SaltEngine::engineLoop() {

    //list<ObjectPtr> objectsForUpdate = getActiveObjects();

    /*BOOST_FOREACH(ObjectPtr obj, objectsForUpdate) {

        

    }*/

}
