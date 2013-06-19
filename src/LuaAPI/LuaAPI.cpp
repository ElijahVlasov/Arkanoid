#include <cmath>

#include <exception>
#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include <Engine.hpp>
#include <Utils.hpp>

#include <LuaAPI.hpp>
#include <LuaAPI/LuaAPI.hpp>

using namespace std;

using namespace luabind;

using namespace Engine;

using namespace LuaAPI;

using namespace Utils;
using namespace Utils::FreeType;
using namespace Utils::UI;



LuaAPI_::LuaAPI_():
    game_(Game::getInstance()),
    menuGameState_(GameStates::MenuState::getInstance()),
    lua_(Lua::getInstance()),
    resourceManager_(ResourceManager::getInstance()),
    audio_(Audio::getInstance())
{

    lua_State* L = lua_->getLuaState();

    module(L, "system")
    [

        class_<Game>("game")
            .def("free", &Game::Free)
            .def("set_screen_rect", &Game::setScreenRect)
            .property("width",  &Game::getScreenWidth)
            .property("height", &Game::getScreenHeight),

        def("game", &Game::getInstance),

        class_<LuaAPI_>("direction")
            .enum_("")
                [

                    value("up",     Direction::UP),
                    value("down",   Direction::DOWN),
                    value("right",  Direction::RIGHT),
                    value("left",   Direction::LEFT)

                ],

        class_<Texture, boost::shared_ptr<Texture> >("texture")
            .property("name",   &Texture::getName)
            .property("width",  &Texture::getWidth,  &Texture::setWidth)
            .property("height", &Texture::getHeight, &Texture::setHeight),

        class_<Sound, boost::shared_ptr<Sound> >("sound"),

        class_<Font, boost::shared_ptr<Font> >("font"),

        def("sound",        LuaAPI_::System_LoadSound),
        def("texture",      LuaAPI_::System_LoadTexture),
        def("play_sound",   LuaAPI_::System_PlaySound),
        def("draw_texture", LuaAPI_::System_DrawTexture),
        def("exit",         LuaAPI_::System_Quit),

        class_<MouseButton>("mouse_btn")
            .enum_("") [

                value("none",   MouseButton::BUTTON_NONE),
                value("left",   MouseButton::BUTTON_LEFT),
                value("right",  MouseButton::BUTTON_RIGHT),
                value("middle", MouseButton::BUTTON_MIDDLE)

            ],

        namespace_("ui") [

            class_<Event>("event")
                .def_readonly("sender", &Event::sender),

            class_<MouseEvent, Event>("mouse_event")
                .enum_("mouse_button") [

                    value("none",   MouseButton::BUTTON_NONE),
                    value("left",   MouseButton::BUTTON_LEFT),
                    value("right",  MouseButton::BUTTON_RIGHT),
                    value("middle", MouseButton::BUTTON_MIDDLE)

                ]
                .def_readonly("button", &MouseEvent::mouseButton)
                .def_readonly("x",      &MouseEvent::x)
                .def_readonly("y",      &MouseEvent::y),


            class_<KeyEvent, Event>("key_event")
                .def_readonly("key", &KeyEvent::key),

            class_<Component, boost::shared_ptr<Component> >("component")
                .def("set_rect",    &Component::setRect)
                .def("draw",        &Component::draw)
                .def("is_contains", &Component::isContains)

                .def("set_hovered_event_handler",    &LuaAPI_::Lua_ComponentSetters::setHoveredEvent)
                .def("set_clicked_event_handler",    &LuaAPI_::Lua_ComponentSetters::setClickedEvent)
                .def("set_mouse_down_event_handler", &LuaAPI_::Lua_ComponentSetters::setMouseDownEvent)
                .def("set_mouse_up_event_handler",   &LuaAPI_::Lua_ComponentSetters::setMouseUpEvent)
                .def("set_draw_event_handler",       &LuaAPI_::Lua_ComponentSetters::setDrawEvent)
                .def("set_key_down_event_handler",   &LuaAPI_::Lua_ComponentSetters::setKeyDownEvent)
                .def("set_key_up_event_handler",     &LuaAPI_::Lua_ComponentSetters::setKeyUpEvent)

                .property("x",      &Component::getX)
                .property("y",      &Component::getY)
                .property("width",  &Component::getWidth)
                .property("height", &Component::getHeight)
                .property("font",   (Font& (Component::*)(void))&Component::getFont)

                .property("text",   &Component::getText, (void (Component::*)(const char*))&Component::setText),

            class_<Button,    Component, boost::shared_ptr<Button> >("button")
                .def(constructor<>()),

            class_<Label,     Component, boost::shared_ptr<Label> >("label")
                .def(constructor<>()),

            class_<Container, Component, boost::shared_ptr<Container> >("container")
                .def("add_component", &Container::addComponent),

            class_<Menu,      Container, boost::shared_ptr<Menu> >("menu")
                .def(constructor<>()),

            class_<Dialog,    Container, boost::shared_ptr<Dialog> >("dialog")
                .def(constructor<>())


        ]

    ];

}



LuaAPI_::~LuaAPI_() {

    if(game_ != 0) {
        game_->Free();
    }

    if(menuGameState_ != 0) {
        menuGameState_->Free();
    }

    if(lua_ != 0) {
        lua_->Free();
    }

    if(resourceManager_ != 0) {
        resourceManager_->Free();
    }

    if(audio_ != 0) {
        audio_->Free();
    }

}



void LuaAPI_::System_LoadScript(const char* name) {

    instance_->lua_->loadScript(name);

}



boost::shared_ptr<Sound> LuaAPI_::System_LoadSound(const char* name) {

    try {

        boost::shared_ptr<Resource> soundResource = instance_->resourceManager_->getResource(ResourceLoader::ResourceType::SOUND, name);

        return boost::dynamic_pointer_cast<Sound>(soundResource);

    } catch(const std::exception&) {}

    return boost::shared_ptr<Sound>();

}



boost::shared_ptr<Texture> LuaAPI_::System_LoadTexture(const char* name)  {

    try {

        boost::shared_ptr<Resource> textureResource = instance_->resourceManager_->getResource(ResourceLoader::ResourceType::TEXTURE, name);

        return boost::dynamic_pointer_cast<Texture>(textureResource);

    } catch(const std::exception&) {}

    return boost::shared_ptr<Texture>();

}



void LuaAPI_::System_PlaySound(const boost::shared_ptr<Sound>& sound) {

    instance_->audio_->playSound(*sound);

}



void LuaAPI_::System_DrawTexture(float x, float y, const boost::shared_ptr<Texture>& texture, Direction direction) {

    Graphics::CoordArray coordAr;

    switch (direction)
    {

        case Engine::UP: {

            coordAr = Graphics::UP_COORDS;

        }
        break;

        case Engine::DOWN:{

            coordAr = Graphics::DOWN_COORDS;

        }
        break;

        case Engine::RIGHT:{

            coordAr = Graphics::RIGHT_COORDS;

        }
        break;

        case Engine::LEFT:{

            coordAr = Graphics::LEFT_COORDS;

        }
        break;

    }

    Graphics::DrawTexture(x, y, texture->getWidth(), texture->getHeight(), coordAr, *texture);

}



void LuaAPI_::System_Quit() {

    instance_->game_->quit();

}



void LuaAPI_::System_ShowDialog(const char* name) {

}



void LuaAPI_::System_ShowMenu(const char* name) {

    try {

        MenuFactory* menuFactory = MenuFactory::getInstance();

        try {

            boost::shared_ptr<Resource> menuResource = instance_->resourceManager_->getResource(ResourceLoader::ResourceType::PLAIN_TEXT, name);

            Menu* menu = menuFactory->createFromXML(menuResource->getData());

            boost::shared_ptr<Menu> menuPtr(menu);

            instance_->menuGameState_->setMenu(menuPtr);

            instance_->game_->setState(instance_->menuGameState_);

        } catch(const std::exception&) {

            menuFactory->Free();

        }

    } catch(const runtime_error&) {}

}



void LuaAPI_::Lua_ComponentSetters::setHoveredEvent(boost::shared_ptr<Component> component, luabind::object eventHandler) {

    try {

        ComponentEvent_wrapper<MouseEvent> wrap(eventHandler);

        component->setHoveredEvent(wrap);

    } catch(const invalid_argument&) {}

}



void LuaAPI_::Lua_ComponentSetters::setClickedEvent(boost::shared_ptr<Component> component, luabind::object eventHandler) {

    try {

        ComponentEvent_wrapper<MouseEvent> wrap(eventHandler);

        component->setClickedEvent(wrap);

    } catch(const invalid_argument&) {}

}



void LuaAPI_::Lua_ComponentSetters::setMouseDownEvent(boost::shared_ptr<Component> component, luabind::object eventHandler) {

    try {

        ComponentEvent_wrapper<MouseEvent> wrap(eventHandler);

        component->setMouseDownEvent(wrap);

    } catch(const invalid_argument&) {}

}



void LuaAPI_::Lua_ComponentSetters::setMouseUpEvent(boost::shared_ptr<Component> component, luabind::object eventHandler) {

    try {

        ComponentEvent_wrapper<MouseEvent> wrap(eventHandler);

        component->setMouseUpEvent(wrap);

    } catch(const invalid_argument&) {}

}



void LuaAPI_::Lua_ComponentSetters::setDrawEvent(boost::shared_ptr<Component> component, luabind::object eventHandler) {

    try {

        ComponentEvent_wrapper<Event> wrap(eventHandler);

        component->setDrawEvent(wrap);

    } catch(const invalid_argument&) {}

}



void LuaAPI_::Lua_ComponentSetters::setKeyDownEvent(boost::shared_ptr<Component> component, luabind::object eventHandler) {

    try {

        ComponentEvent_wrapper<KeyEvent> wrap(eventHandler);

        component->setKeyDownEvent(wrap);

    } catch(const invalid_argument&) {}

}



void LuaAPI_::Lua_ComponentSetters::setKeyUpEvent(boost::shared_ptr<Component> component, luabind::object eventHandler) {

    try {

        ComponentEvent_wrapper<KeyEvent> wrap(eventHandler);

        component->setKeyUpEvent(wrap);

    } catch(const invalid_argument&) {}

}
