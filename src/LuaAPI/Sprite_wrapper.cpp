#include <LuaAPI/Sprite_wrapper.hpp>

#include <Utils/Graphics/Sprite.hpp>


using namespace LuaAPI;

using namespace Utils::Graphics;



Sprite_wrapper::Sprite_wrapper():
    Sprite()
{}



Sprite_wrapper::~Sprite_wrapper() {}



void Sprite_wrapper::onRender(const GeometryDefines::Point& point) {

    call<void>("on_render_p", point);

}



void Sprite_wrapper::onRender(const GeometryDefines::PointI& point) {

    call<void>("on_render_pi", point);

}



void Sprite_wrapper::default_onRender(boost::shared_ptr<Sprite> sprite, const GeometryDefines::PointI& point) {

    sprite->onRender(point);

}



void Sprite_wrapper::onRender(const GeometryDefines::Box& box) {

    call<void>("on_render_b", box);

}



void Sprite_wrapper::onRender(const GeometryDefines::BoxI& box) {

    call<void>("on_render_bi", box);

}



void Sprite_wrapper::default_onRender(boost::shared_ptr<Sprite> sprite, const GeometryDefines::BoxI& box) {

    sprite->onRender(box);

}



void Sprite_wrapper::onRender(const GeometryDefines::Polygon& polygon) {

    call<void>("on_render_pol", polygon);

}



void Sprite_wrapper::onRender(const GeometryDefines::PolygonI& polygon) {

    call<void>("on_render_poli", polygon);

}



void Sprite_wrapper::default_onRender(boost::shared_ptr<Sprite> sprite, const GeometryDefines::PolygonI& polygon) {

    sprite->onRender(polygon);

}
