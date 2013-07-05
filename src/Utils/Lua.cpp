#include <cstring>

#include <algorithm>
#include <fstream>
#include <ios>
#include <stdexcept>
#include <string>

#include <boost/format.hpp>

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include <Utils/assert.hpp>
#include <Utils/Lua.hpp>
#include <Utils/ResourceManager.hpp>


using namespace std;
using namespace Utils;



Lua::Lua():
    resourceManager_(ResourceManager::getInstance()),
    luaState_(lua_open()) // Подготавливаем Lua VM
{

    luaL_openlibs(luaState_);
    /*luaopen_base(luaState_);
    luaopen_table(luaState_);
    luaopen_io(luaState_);
    luaopen_string(luaState_);
    luaopen_math(luaState_);*/

    luabind::open(luaState_); // подключаем luabind

}



Lua::~Lua() {

    // закрываем Lua VM
    lua_close(luaState_);

}



string Lua::createModuleName(const string& name) {

    string moduleName = name;

    size_t index = moduleName.rfind(".lua");

    moduleName.erase(index);

    ::replace(moduleName.begin(), moduleName.end(), '/', '.');

    return moduleName;

}



void Lua::loadScript(const string& name) throw(runtime_error, invalid_argument) {

    ASSERT(
        (!name.empty()),
        invalid_argument("name")
    );

    string moduleName = createModuleName(name);

    string script = resourceManager_->getResource(ResourceManager::ResourceType::PLAIN_TEXT, "scripts/" + name)->getData();

    // Добавляем объявление скрипта, как модуля
    script = (boost::format("module(\"%1%\", package.seeall)\n%2%") % moduleName % script).str();

    int result = luaL_dostring(luaState_, script.c_str());

    ASSERT(
        (result == 0),
        runtime_error(
            (boost::format("Error in %1%:\n\"%2%\"")
                % name
                % lua_tostring(luaState_, -1)
            ).str()
        )
    );

}



void Lua::loadScript(const char* name) throw(runtime_error, invalid_argument) {

    ASSERT(
        (name != 0),
        invalid_argument("name")
    );

    ASSERT(
        (strlen(name) != 0),
        invalid_argument("name")
    );

    loadScript(string(name));

}



lua_State* Lua::getLuaState() {

    return luaState_;

}



lua_State* Lua::getLuaState_newThread() {

    return lua_newthread(luaState_);

}



luabind::object Lua::getFunctionObject(const char* funcName) throw(runtime_error, invalid_argument) {

    ASSERT(
        (funcName != 0),
        invalid_argument("funcName")
    );

    ASSERT(
        (strlen(funcName) != 0),
        invalid_argument("funcName")
    );

    string name = funcName;

    luabind::object module = luabind::globals(luaState_);

    string::iterator point = std::find(name.begin(), name.end(), '.');

    while(point != name.end()) {

        string moduleName(name.begin(), point);

        name.erase(name.begin(), ++point);

        module = module[moduleName];

        point = std::find(name.begin(), name.end(), '.');

    }

    return module[name];

}



luabind::object Lua::getFunctionObject(const string& funcName) throw(runtime_error, invalid_argument) {

    return getFunctionObject(funcName.c_str());

}
