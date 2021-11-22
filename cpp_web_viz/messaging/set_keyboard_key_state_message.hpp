#pragma once

#include <string>

#include <nlohmann/json.hpp>

#include <cpp_web_viz/messaging/key_codes.hpp>

namespace cpp_web_viz {

namespace MessageType {
  extern std::string SetKeyboardKeyStateMessage;
}  // namespace MessageType

class SetKeyboardKeyStateMessage
{
 public:
  SetKeyboardKeyStateMessage();

  SetKeyboardKeyStateMessage(const KeyCode key_code_, const bool is_pressed_);

  KeyCode key_code;
  bool is_pressed;
};

/*
 * @brief - Converts from JSON. See https://github.com/nlohmann/json#arbitrary-types-conversions.
 */
void from_json(const nlohmann::json& json, SetKeyboardKeyStateMessage& set_mouse_position_message);

}  // namespace cpp_web_viz
