#pragma once

#include <string>

#include <nlohmann/json.hpp>

namespace cpp_web_viz {

namespace MessageType {
  extern std::string SetMousePositionMessage;
}  // namespace MessageType

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
