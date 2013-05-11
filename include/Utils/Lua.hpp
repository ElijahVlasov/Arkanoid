/*****************************************
	
    Синглтон, отвечающий за управление
	lua - скриптами.

*****************************************/

#ifndef _SALT2D_UTILS_LUA_HPP
#define _SALT2D_UTILS_LUA_HPP

#include <stdexcept>
#include <string>

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include <Utils/Singleton.hpp>

namespace Utils {
	
	class Lua: public Utils::Singleton<Lua> {

		SINGLETON(Lua)
	
		public:

			// Загрузить скрипт. Если возникает ошибка выполнения скрипта или
			// этот скрипт не найден, то генерируется runtime_error.
			// Если scriptName == NULL или scriptName - пустая строка,
			// то генерируется invalid_argument
			void loadScript(const char* scriptName)			throw(std::runtime_error, std::invalid_argument);
			void loadScript(const std::string& scriptName)		throw(std::runtime_error, std::invalid_argument);

			lua_State* getLuaState();
			lua_State* getLuaState_newThread();

			luabind::object getFunctionObject(const char* funcName)
										throw(std::runtime_error, std::invalid_argument);

			luabind::object getFunctionObject(const std::string& funcName)
										throw(std::runtime_error, std::invalid_argument);

		protected:
			
			Lua();
			~Lua();

		private:

			lua_State* luaState_;

			
			Lua(const Lua&);

			std::string createModuleName(const std::string& scriptName);
			std::string createScriptPath(const std::string& scriptName);

	};

}

#endif
