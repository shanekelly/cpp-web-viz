#include "rendering/polygon.hpp"

namespace cpp_web_viz {

Polygon::Polygon()
  : vertices({}), edge_color({0, 0, 0, 0}), fill_color({0, 0, 0, 0}) {}

Polygon::Polygon(const std::vector<PositionInPixels>& vertices_, const RGBA& edge_color_,
                 const RGBA& fill_color_)
    : vertices(vertices_), edge_color(edge_color_), fill_color(fill_color_) {}

void Polygon::Translate(const PositionInPixels& t) {
  std::transform(vertices.begin(), vertices.end(), vertices.begin(),
    [&t](const PositionInPixels& vertex) -> PositionInPixels {
      return vertex + t;
    });
}

void to_json(nlohmann::json& json, const Polygon& polygon) {
  json = nlohmann::json{
    {"vertices", polygon.vertices},
    {"edge_color", polygon.edge_color},
    {"fill_color", polygon.fill_color}};
}

}  // namespace cpp_web_viz
