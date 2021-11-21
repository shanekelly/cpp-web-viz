#pragma once

#include <string>
#include <vector>

#include "rendering/polygon.hpp"

namespace cpp_web_viz {

namespace MessageType {
  extern std::string SetCanvasSizeMessage;
  extern std::string SetRenderablesMessage;
  extern std::string SetMousePositionMessage;
}  // namespace MessageType

class SetCanvasSizeMessage
{
 public:
  SetCanvasSizeMessage(const int canvas_width_, const int canvas_height_);

  int canvas_width;
  int canvas_height;
};

/*
 * @brief - Converts to JSON. See https://github.com/nlohmann/json#arbitrary-types-conversions.
 */
void to_json(nlohmann::json& json, const SetCanvasSizeMessage set_canvas_size_message);

class SetRenderablesMessage
{
 public:
  SetRenderablesMessage(const std::vector<Polygon>& polygons_to_render_);

  std::vector<Polygon> polygons_to_render;
};

/*
 * @brief - Converts to JSON. See https://github.com/nlohmann/json#arbitrary-types-conversions.
 */
void to_json(nlohmann::json& json, const SetRenderablesMessage set_renderables_message);

class SetMousePositionMessage
{
 public:
  SetMousePositionMessage();

  SetMousePositionMessage(const int mouse_position_x_, const int mouse_position_y_);

  int mouse_position_x;
  int mouse_position_y;
};

/*
 * @brief - Converts from JSON. See https://github.com/nlohmann/json#arbitrary-types-conversions.
 */
void from_json(const nlohmann::json& json, SetMousePositionMessage& set_mouse_position_message);

}  // namespace cpp_web_viz
