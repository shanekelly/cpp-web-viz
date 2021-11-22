#include <cpp_web_viz/messaging/set_mouse_position_message.hpp>

namespace cpp_web_viz {

namespace MessageType {
  std::string SetMousePositionMessage = "SetMousePositionMessage";
}  // namespace MessageType

SetMousePositionMessage::SetMousePositionMessage()
  : mouse_position_x(0), mouse_position_y(0)
{
}

SetMousePositionMessage::SetMousePositionMessage(const int mouse_position_x_, const int mouse_position_y_)
  : mouse_position_x(mouse_position_x_), mouse_position_y(mouse_position_y_)
{
}

void from_json(const nlohmann::json& json, SetMousePositionMessage& set_mouse_position_message)
{
  json.at("message_data").at("mouse_position_x").get_to(set_mouse_position_message.mouse_position_x);
  json.at("message_data").at("mouse_position_y").get_to(set_mouse_position_message.mouse_position_y);
}

}  // namespace cpp_web_viz
