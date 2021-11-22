#include <cpp_web_viz/rendering/messages.hpp>

#include <iostream>

namespace cpp_web_viz {

namespace MessageType {
  std::string SetCanvasSizeMessage = "SetCanvasSizeMessage";
  std::string SetRenderablesMessage = "SetRenderablesMessage";
  std::string SetMousePositionMessage = "SetMousePositionMessage";
  std::string SetKeyboardKeyStateMessage = "SetKeyboardKeyStateMessage";
}  // namespace MessageType

SetCanvasSizeMessage::SetCanvasSizeMessage(const int canvas_width_, const int canvas_height_)
  : canvas_width(canvas_width_), canvas_height(canvas_height_) {}

void to_json(nlohmann::json& json, const SetCanvasSizeMessage set_canvas_size_message) {
  json = nlohmann::json{};
  json["message_type"] = MessageType::SetCanvasSizeMessage;
  json["message_data"]["canvas_width"] = set_canvas_size_message.canvas_width;
  json["message_data"]["canvas_height"] = set_canvas_size_message.canvas_height;
}

SetRenderablesMessage::SetRenderablesMessage(const std::vector<Circle>& circles_to_render_,
  const std::vector<Polygon>& polygons_to_render_)
  : circles_to_render(circles_to_render_), polygons_to_render(polygons_to_render_)
{
}

void to_json(nlohmann::json& json, const SetRenderablesMessage set_renderables_message) {
  json = nlohmann::json{};
  json["message_type"] = MessageType::SetRenderablesMessage;
  json["message_data"]["circles_to_render"] = set_renderables_message.circles_to_render;
  json["message_data"]["polygons_to_render"] = set_renderables_message.polygons_to_render;
}

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
