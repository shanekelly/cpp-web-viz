#pragma once

#include <string>
#include <vector>

#include <cpp_web_viz/rendering/circle.hpp>
#include <cpp_web_viz/rendering/polygon.hpp>

namespace cpp_web_viz {

namespace MessageType {
  extern std::string SetRenderablesMessage;
}  // namespace MessageType

class SetRenderablesMessage
{
 public:
  SetRenderablesMessage(const std::vector<Circle>& circles_to_render_,
    const std::vector<Polygon>& polygons_to_render_);

  std::vector<Circle> circles_to_render;
  std::vector<Polygon> polygons_to_render;
};

/*
 * @brief - Converts to JSON. See https://github.com/nlohmann/json#arbitrary-types-conversions.
 */
void to_json(nlohmann::json& json, const SetRenderablesMessage set_renderables_message);

}  // namespace cpp_web_viz
