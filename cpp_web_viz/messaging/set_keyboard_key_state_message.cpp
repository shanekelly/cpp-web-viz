#include <cpp_web_viz/messaging/set_keyboard_key_state_message.hpp>

namespace cpp_web_viz {

namespace MessageType {
  std::string SetKeyboardKeyStateMessage = "SetKeyboardKeyStateMessage";
}  // namespace MessageType

SetKeyboardKeyStateMessage::SetKeyboardKeyStateMessage()
  : key_code(KeyCode::None), is_pressed(false)
{
}

SetKeyboardKeyStateMessage::SetKeyboardKeyStateMessage(const KeyCode key_code_, const bool is_pressed_)
  : key_code(key_code_), is_pressed(is_pressed_)
{
}

void from_json(const nlohmann::json& json, SetKeyboardKeyStateMessage& set_keyboard_key_state_message)
{
  json.at("message_data").at("key_code").get_to(set_keyboard_key_state_message.key_code);
  json.at("message_data").at("is_pressed").get_to(set_keyboard_key_state_message.is_pressed);
}

}  // namespace cpp_web_viz
