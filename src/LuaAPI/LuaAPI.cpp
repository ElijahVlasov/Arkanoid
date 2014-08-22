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
using namespace Utils::Audio;
using namespace Utils::Graphics;
using namespace Utils::FreeType;
using namespace Utils::UI;



LuaAPI_::LuaAPI_():
    game_(              Game::getInstance()					),
    menuGameState_(     GameStates::MenuState::getInstance()),
    lua_(               Lua::getInstance()					),
    resourceManager_(   ResourceManager::getInstance()		),
    audioManager_(      AudioManager::getInstance()		    )
{

    lua_State* L = lua_->getLuaState();

    namespace gd = GeometryDefines;

    module(L, "system") [


        //////////////////////////////// Ресурсы: ///////////////////////////////////

        class_<Texture, boost::shared_ptr<Texture> >("texture")
            .property("name",   &Texture::getName)
            .property("width",  &Texture::getWidth)
            .property("height", &Texture::getHeight),

        class_<Sound, boost::shared_ptr<Sound> >("sound"),

        class_<Font, boost::shared_ptr<Font> >("font"),

        ////////////////////////////////////////////////////////////////////////////

        class_<SoundPlayer, boost::shared_ptr<SoundPlayer> >("sound_player")
            .def("play",  &SoundPlayer::play)
            .def("pause", &SoundPlayer::pause)
            .def("stop",  &SoundPlayer::stop),

        // Конструкторы для звуков и текстур
        def("sound",        &LuaAPI_::System_LoadSound),
        def("texture",      &LuaAPI_::System_LoadTexture),
        def("font",         &LuaAPI_::System_LoadFont),
        /////////////////////////////////////

        def("sound_player", &LuaAPI_::System_CreateSoundPlayer),

        def("get_screen_width",  &LuaAPI_::System_GetScreenWidth),
        def("get_screen_height", &LuaAPI_::System_GetScreenHeight),
        def("set_screen_rect",   &LuaAPI_::System_SetScreenRect),

        def("get_main_menu",  &LuaAPI_::System_GetMainMenu),
        def("get_pause_menu", &LuaAPI_::System_GetPauseMenu),

        def("exit",         &LuaAPI_::System_Quit),

        def("load_script",  &LuaAPI_::System_LoadScript),

        def("show_dialog",  &LuaAPI_::System_ShowDialog),
        def("show_menu",    &LuaAPI_::System_ShowMenu),

        def("start_game",   &LuaAPI_::System_StartGame),
        def("quit_game",    &LuaAPI_::System_QuitGame),

        class_<MouseButton>("mouse_btn")
            .enum_("") [

                value("none",   MouseButton::BUTTON_NONE),
                value("left",   MouseButton::BUTTON_LEFT),
                value("right",  MouseButton::BUTTON_RIGHT),
                value("middle", MouseButton::BUTTON_MIDDLE)

            ],

        class_<Sprite, Sprite_wrapper, boost::shared_ptr<Sprite> >("sprite")
            .def("on_render_p", (void (Sprite::*)(const gd::Point&) ) &Sprite::onRender)
            .def("on_render_pi", (void (Sprite::*)(const gd::PointI&) ) &Sprite::onRender,
                 (void (*)(boost::shared_ptr<Sprite>, const gd::PointI&) ) &Sprite_wrapper::default_onRender)
            .def("on_render_b", (void (Sprite::*)(const gd::Box&) ) &Sprite::onRender)
            .def("on_render_bi", (void (Sprite::*)(const gd::BoxI&) ) &Sprite::onRender,
                 (void (*)(boost::shared_ptr<Sprite>, const gd::BoxI&) ) &Sprite_wrapper::default_onRender)
            .def("on_render_pol", (void (Sprite::*)(const gd::Polygon&) ) &Sprite::onRender)
            .def("on_render_poli", (void (Sprite::*)(const gd::PolygonI&) ) &Sprite::onRender,
                 (void (*)(boost::shared_ptr<Sprite>, const gd::PolygonI&) ) &Sprite_wrapper::default_onRender),

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

            def("draw_texture_p",    &LuaAPI_::Graphics_DrawTexture<gd::Point>),
            def("draw_texture_pi",   &LuaAPI_::Graphics_DrawTexture<gd::PointI>),
            def("draw_texture_b",    &LuaAPI_::Graphics_DrawTexture<gd::Box>),
            def("draw_texture_bi",   &LuaAPI_::Graphics_DrawTexture<gd::BoxI>),
            def("draw_texture_pol",  &LuaAPI_::Graphics_DrawTexture<gd::Polygon>),
            def("draw_texture_poli", &LuaAPI_::Graphics_DrawTexture<gd::PolygonI>)

        ],

        namespace_("ui") [ // эдементы управления:

            class_<Event>("event"),

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

                .def("set_mouse_motion_event_handler",  &LuaAPI_::Lua_ComponentSetters::setMouseMotionEvent)
                .def("set_hovered_event_handler",       &LuaAPI_::Lua_ComponentSetters::setHoveredEvent)
                .def("set_leaved_event_handler",        &LuaAPI_::Lua_ComponentSetters::setLeavedEvent)
                .def("set_clicked_event_handler",       &LuaAPI_::Lua_ComponentSetters::setClickedEvent)
                .def("set_mouse_down_event_handler",    &LuaAPI_::Lua_ComponentSetters::setMouseDownEvent)
                .def("set_mouse_up_event_handler",      &LuaAPI_::Lua_ComponentSetters::setMouseUpEvent)
                .def("set_draw_event_handler",          &LuaAPI_::Lua_ComponentSetters::setDrawEvent)
                .def("set_key_down_event_handler",      &LuaAPI_::Lua_ComponentSetters::setKeyDownEvent)
                .def("set_key_up_event_handler",        &LuaAPI_::Lua_ComponentSetters::setKeyUpEvent)

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

    /*module(L, "engine") [

        class_<Object, Object_wrapper, ObjectPtr>("object")
            .def("on_collision",        &Object::onCollision)
            .def("on_render",           &Object::onRender,    &Object_wrapper::default_onRender)
            .def("live",                &Object::live)
            .def("move",                &Object::move,        &Object_wrapper::default_move)
            .def("spin",                &Object::spin,        &Object_wrapper::default_spin)
//            .def("get_center"           &Object::getCenter, &Object_wrapper::default_getCenter)
            .property("location",       &Object::getLocation, &Object::setLocation),



        class_<Location, LocationPtr >("location")
            .def(constructor<>())
            .property("ground_texture", &Location::getGroundTexture, &Location::setGroundTexture)
            .property("width",          &Location::getWidth,         &Location::setWidth)
            .property("height",         &Location::getHeight,        &Location::setHeight)
            .property("name",           &Location::getName,          (void (Location::*)(const string&))&Location::setName)


    ];*/

}



boost::shared_ptr<Font> LuaAPI_::System_LoadFont(const char* name) {

    try {

        return instance_->resourceManager_->getResource<Font>(name);

    } catch(const std::exception&) {}

    return boost::shared_ptr<Font>();

}



void LuaAPI_::System_LoadScript(const char* name) {

    try {

        instance_->lua_->loadScript(name);

    } catch(const runtime_error&) {}
      catch(const invalid_argument) {}

}



boost::shared_ptr<Sound> LuaAPI_::System_LoadSound(const char* name) {

    try {

        return instance_->resourceManager_->getResource<Sound>(name);

    } catch(const std::exception&) {}

    return boost::shared_ptr<Sound>();

}



boost::shared_ptr<Texture> LuaAPI_::System_LoadTexture(const char* name)  {

    try {

        return instance_->resourceManager_->getResource<Texture>(name);

    } catch(const std::exception&) {}

    return boost::shared_ptr<Texture>();

}



boost::shared_ptr<Utils::Audio::SoundPlayer>  LuaAPI_::System_CreateSoundPlayer(const boost::shared_ptr<Sound>& sound) {

    instance_->audioManager_->createSoundPlayer(sound);

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



void LuaAPI_::System_StartGame() {

	instance_->game_->startGame();

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

        SingletonPointer<MenuBuilder> menuBuilder = MenuBuilder::getInstance();

        Menu* menu = menuBuilder->createMenu(instance_->resourceManager_->getFileData(name));

        boost::shared_ptr<Menu> menuPtr(menu);

        instance_->menuGameState_->setMenu(menuPtr);

        instance_->game_->setState(instance_->menuGameState_.get());

    } catch(const runtime_error&) {}

}



void LuaAPI_::Lua_ComponentSetters::setMouseMotionEvent(boost::shared_ptr<Component> component, luabind::object eventHandler) {

    try {

        ComponentEvent_wrapper<MouseEvent> wrap(eventHandler);

        component->setMouseMotionEvent(wrap);

    } catch(const invalid_argument&) {}

}



void LuaAPI_::Lua_ComponentSetters::setHoveredEvent(boost::shared_ptr<Component> component, luabind::object eventHandler) {

    try {

        ComponentEvent_wrapper<Event> wrap(eventHandler);

        component->setHoveredEvent(wrap);

    } catch(const invalid_argument&) {}

}



void LuaAPI_::Lua_ComponentSetters::setLeavedEvent(boost::shared_ptr<Component> component, luabind::object eventHandler) {

    try {

        ComponentEvent_wrapper<Event> wrap(eventHandler);

        component->setLeavedEvent(wrap);

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
