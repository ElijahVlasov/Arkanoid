#ifndef _SALT2D_UTILS_LUA_HPP
#define _SALT2D_UTILS_LUA_HPP

#include <stdexcept>
#include <string>

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include <Utils/ResourceManager.hpp>
#include <Utils/Singleton.hpp>
#include <Utils/SingletonPointer.hpp>

namespace Utils {

    /** Класс для управления Lua-скриптами.
      * @author Elijah Vlasov
    */

    class Lua: public Utils::Singleton<Lua> {

        SINGLETON(Lua)

        public:

            /** Загрузить скрипт.
              * @throw Генерирует std::runtime_error, если возникает ошибка
              * выполнения скрипта или скрипт не найден
              * Если scriptName == NULL или scriptName - пустая строка,
              * то генерируется std::invalid_argument
            */

            void loadScript(const char* scriptName)        throw(std::runtime_error, std::invalid_argument);

            /** Загрузить скрипт.
              * @throw Генерирует std::runtime_error, если возникает ошибка
              * выполнения скрипта или скрипт не найден
              * Если scriptName - пустая строка,
              * то генерируется std::invalid_argument
            */

            void loadScript(const std::string& scriptName) throw(std::runtime_error, std::invalid_argument);

            /** Указатель на состояние Lua.
            */

            lua_State* getLuaState();

            /** Равносильно lua_newthread(getLuaState());
            */

            lua_State* getLuaState_newThread();

            /** Получить объект функции.
              * @param funcName имя функции Lua вида "func_table.func_table2. ... .func_name"
              * @throw Генерирует std::runtime_error, если не удается найти функцию. Генерирует
              *        std::invalid_argument, если funcName == NULL или funcName пустая строка
            */

            luabind::object getFunctionObject(const char* funcName)
                                                           throw(std::runtime_error, std::invalid_argument);

            /** Получить объект функции.
              * @param funcName имя функции Lua вида "func_table.func_table2. ... .func_name"
              * @throw Генерирует std::runtime_error, если не удается найти функцию. Генерирует
              *        std::invalid_argument, если funcName пустая строка
            */

            luabind::object getFunctionObject(const std::string& funcName)
                                                           throw(std::runtime_error, std::invalid_argument);

        protected:

            Lua();
            ~Lua();

        private:

            SingletonPointer<ResourceManager> resourceManager_;

            lua_State* luaState_;

            std::string createModuleName(const std::string& scriptName);

    };

}

#endif
