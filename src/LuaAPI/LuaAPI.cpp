#include <cmath>

#include <exception>
#include <stdexcept>
#include <string>

#include <boost/get_pointer.hpp>
#include <boost/shared_ptr.hpp>

#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <luabind/iterator_policy.hpp>

#include <Engine.hpp>
#include <Utils.hpp>

#include <LuaAPI.hpp>
#include <LuaAPI/LuaAPI.hpp>

#include "geometry_defines.hpp"

using namespace std;

using namespace luabind;

using namespace Engine;

using namespace LuaAPI;

using namespace Utils;
using namespace Utils::FreeType;
using namespace Utils::UI;



//namespace luabind {

    /*namespace detail {

            namespace has_get_pointer_ {*/

                template<class T>
                T * get_pointer(SingletonPointer<T> const& p) { return p.get(); }

       /*     }

    }*/

/*}*/



LuaAPI_::LuaAPI_():
    game_(              Game::getInstance()					),
    menuGameState_(     GameStates::MenuState::getInstance()),
    lua_(               Lua::getInstance()					),
    resourceManager_(   ResourceManager::getInstance()		),
    audio_(             Audio::getInstance()				)
{

    lua_State* L = lua_->getLuaState();

    namespace gd = GeometryDefines;

    module(L, "system") [

        class_<LuaAPI_>("direction")
            .enum_("")
                [

                    value("up",     Direction::UP),
                    value("down",   Direction::DOWN),
                    value("right",  Direction::RIGHT),
                    value("left",   Direction::LEFT)

                ],

        //////////////////////////////// Ресурсы: ///////////////////////////////////

        class_<Texture, boost::shared_ptr<Texture> >("texture")
            .property("name",   &Texture::getName)
            .property("width",  &Texture::getWidth,  &Texture::setWidth)
            .property("height", &Texture::getHeight, &Texture::setHeight),

        class_<Sound, boost::shared_ptr<Sound> >("sound"),

        class_<Font, boost::shared_ptr<Font> >("font"),

        ////////////////////////////////////////////////////////////////////////////

        // Конструкторы для звуков и текстур
        def("sound",        &LuaAPI_::System_LoadSound),
        def("texture",      &LuaAPI_::System_LoadTexture),
        /////////////////////////////////////

        def("get_screen_width",  &LuaAPI_::System_GetScreenWidth),
        def("get_screen_height", &LuaAPI_::System_GetScreenHeight),
        def("set_screen_rect",   &LuaAPI_::System_SetScreenRect),

        def("get_main_menu",  &LuaAPI_::System_GetMainMenu),
        def("get_pause_menu", &LuaAPI_::System_GetPauseMenu),

        def("play_sound",   &LuaAPI_::System_PlaySound),
        def("exit",         &LuaAPI_::System_Quit),

        def("load_script",  &LuaAPI_::System_LoadScript),

        class_<MouseButton>("mouse_btn")
            .enum_("") [

                value("none",   MouseButton::BUTTON_NONE),
                value("left",   MouseButton::BUTTON_LEFT),
                value("right",  MouseButton::BUTTON_RIGHT),
                value("middle", MouseButton::BUTTON_MIDDLE)

            ],

        namespace_("geometry") [

            class_<gd::Point>("point")
                .def(constructor<>())
                .def(constructor<float, float>())
                .property("x", (const float& (gd::Point::*)() const) &gd::Point::x,
                            (void (gd::Point::*)(const float&)) &gd::Point::x )
                .property("y", (const float& (gd::Point::*)() const) &gd::Point::y,
                            (void (gd::Point::*)(const float&)) &gd::Point::y ),

            class_<gd::PointI>("point_i")
                .def(constructor<>())
                .def(constructor<int, int>())
                .property("x", (const int& (gd::PointI::*)() const) &gd::PointI::x,
                            (void (gd::PointI::*)(const int&)) &gd::PointI::x )
                .property("y", (const int& (gd::PointI::*)() const) &gd::PointI::y,
                            (void (gd::PointI::*)(const int&)) &gd::PointI::y ),

            class_<gd::Box>("box")
                .def(constructor<>())
                .def(constructor<gd::Point, gd::Point>())
                .property("min_corner", (const gd::Point& (gd::Box::*)() const)&gd::Box::min_corner,
                          &LuaAPI_::Lua_BoxSetters::setMinCorner<gd::Box, gd::Point>)
                .property("max_corner", (const gd::Point& (gd::Box::*)() const)&gd::Box::max_corner,
                          &LuaAPI_::Lua_BoxSetters::setMaxCorner<gd::Box, gd::Point>),

            class_<gd::BoxI>("box_i")
                .def(constructor<>())
                .def(constructor<gd::PointI, gd::PointI>())
                .property("min_corner", (const gd::PointI& (gd::BoxI::*)() const)&gd::BoxI::min_corner,
                          &LuaAPI_::Lua_BoxSetters::setMinCorner<gd::BoxI, gd::PointI>)
                .property("max_corner", (const gd::PointI& (gd::BoxI::*)() const)&gd::BoxI::max_corner,
                          &LuaAPI_::Lua_BoxSetters::setMaxCorner<gd::BoxI, gd::PointI>),

            class_<gd::Polygon>("polygon")
                .def(constructor<>())
                .def("add_point", &LuaAPI_::Polygon_addPoint<gd::Polygon>)
                .property("points", (const gd::Polygon::ring_type& (gd::Polygon::*)() const)&gd::Polygon::outer, return_stl_iterator),

            class_<gd::PolygonI>("polygon")
                .def(constructor<>())
                .def("add_point", &LuaAPI_::Polygon_addPoint<gd::PolygonI>)
                .property("points", (const gd::PolygonI::ring_type& (gd::PolygonI::*)() const)&gd::PolygonI::outer, return_stl_iterator)

        ],

        namespace_("graphics") [

            def("draw_texture", &LuaAPI_::Graphics_DrawTexture<gd::Point>),
            def("draw_texture", &LuaAPI_::Graphics_DrawTexture<gd::PointI>),
            def("draw_texture", &LuaAPI_::Graphics_DrawTexture<gd::Box>),
            def("draw_texture", &LuaAPI_::Graphics_DrawTexture<gd::BoxI>),
            def("draw_texture", &LuaAPI_::Graphics_DrawTexture<gd::Polygon>),
            def("draw_texture", &LuaAPI_::Graphics_DrawTexture<gd::PolygonI>)

        ],

        namespace_("ui") [ // эдементы управления:

            class_<Event>("event"),
                //.def_readwrite("sender", &Event::sender),

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

                .property("text",   &Component::getText, (void (Component::*)(const std::string&))&Component::setText),

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

    module(L, "engine") [

        class_<Object, Object_wrapper, ObjectPtr>("object"),

        class_<LocationLayer, LocationLayerPtr >("location_layer")
            .def(constructor<>())
            .def("add_object", &LocationLayer::addObject),

        class_<Location, LocationPtr >("location")
            .def(constructor<>())
            .property("ground_texture", &Location::getGroundTexture, &Location::setGroundTexture)
            .property("width", &Location::getWidth, &Location::setWidth)
            .property("height", &Location::getHeight, &Location::setHeight)
            .property("name", &Location::getName, (void (Location::*)(const char*))&Location::setName)


    ];

}



void LuaAPI_::System_LoadScript(const char* name) {

    try {

        instance_->lua_->loadScript(name);

    } catch(const runtime_error&) {}
      catch(const invalid_argument) {}

}



boost::shared_ptr<Sound> LuaAPI_::System_LoadSound(const char* name) {

    try {

        boost::shared_ptr<Resource> soundResource = instance_->resourceManager_->getResource(ResourceManager::ResourceType::SOUND, name);

        return boost::dynamic_pointer_cast<Sound>(soundResource);

    } catch(const std::exception&) {}

    return boost::shared_ptr<Sound>();

}



boost::shared_ptr<Texture> LuaAPI_::System_LoadTexture(const char* name)  {

    try {

        boost::shared_ptr<Resource> textureResource = instance_->resourceManager_->getResource(ResourceManager::ResourceType::TEXTURE, name);

        return boost::dynamic_pointer_cast<Texture>(textureResource);

    } catch(const std::exception&) {}

    return boost::shared_ptr<Texture>();

}



void LuaAPI_::System_PlaySound(const boost::shared_ptr<Sound>& sound) {

    instance_->audio_->playSound(*sound);

}



unsigned int LuaAPI_::System_GetScreenWidth() {

    return instance_->game_->getScreenWidth();

}



unsigned int LuaAPI_::System_GetScreenHeight() {

    return instance_->game_->getScreenHeight();

}



void LuaAPI_::System_SetScreenRect(unsigned int width, unsigned int height) {

    instance_->game_->setScreenRect(width, height);

}



boost::shared_ptr<Menu> LuaAPI_::System_GetMainMenu() {

    return instance_->game_->getMainMenu();

}



boost::shared_ptr<Menu> LuaAPI_::System_GetPauseMenu() {

    return instance_->game_->getPauseMenu();

}



void LuaAPI_::System_StartGame(const char* worldName) {

	instance_->game_->startGame(worldName);

}



void LuaAPI_::System_QuitGame() {

	instance_->game_->quitGame();

}



void LuaAPI_::System_Quit() {

    instance_->game_->quit();

}



void LuaAPI_::System_ShowDialog(const char* name) {

}



SingletonPointer<Game> LuaAPI_::Engine_GetGame() {

    return instance_->game_;

}



void LuaAPI_::System_ShowMenu(const char* name) {

    try {

        SingletonPointer<MenuFactory> menuFactory = MenuFactory::getInstance();

        boost::shared_ptr<Resource> menuResource = instance_->resourceManager_->getResource(ResourceManager::ResourceType::PLAIN_TEXT, name);

        Menu* menu = menuFactory->createFromXML(menuResource->getData());

        boost::shared_ptr<Menu> menuPtr(menu);

        instance_->menuGameState_->setMenu(menuPtr);

        instance_->game_->setState(instance_->menuGameState_.get());

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
