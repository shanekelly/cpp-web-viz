#include <cpp_web_viz/rendering/circle.hpp>

namespace cpp_web_viz {

Circle::Circle()
  : position({0, 0}), radius(0), edge_color({0, 0, 0, 0}), fill_color({0, 0, 0, 0}) {}

Circle::Circle(const PositionInPixels& position_, const float radius_, const RGBA& edge_color_,
                 const RGBA& fill_color_)
    : position(position_), radius(radius_), edge_color(edge_color_), fill_color(fill_color_) {}

void Circle::Translate(const PositionInPixels& t) {
  position = position + t;
}

void to_json(nlohmann::json& json, const Circle& circle) {
  json = nlohmann::json{
    {"position", circle.position},
    {"radius", circle.radius},
    {"edge_color", circle.edge_color},
    {"fill_color", circle.fill_color}};
}

}  // namespace cpp_web_viz
