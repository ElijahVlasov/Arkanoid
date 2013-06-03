#include <mutex>

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include <Engine/WorldLayer.hpp>

#include "Box.pb.h"
#include "Point.pb.h"
#include "World.pb.h"

using namespace std;

using namespace boost::geometry::model;
using namespace boost::geometry::model::d2;

using namespace Engine;



WorldLayer::WorldLayer(){}



WorldLayer::WorldLayer(const EngineData::Layer* layer) {

    const EngineData::Box& box = layer->box();

    const EngineData::Point& e_min_corner = box.min_corner();
    const EngineData::Point& e_max_corner = box.max_corner();

    point_xy<float> min_corner(e_min_corner.x(), e_min_corner.y());
    point_xy<float> max_corner(e_max_corner.x(), e_max_corner.y());

    box_.min_corner() = min_corner;
    box_.max_corner() = max_corner;

}
