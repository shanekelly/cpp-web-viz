#include <cpp_web_viz/messaging/set_canvas_size_message.hpp>

namespace cpp_web_viz {

namespace MessageType {
  std::string SetCanvasSizeMessage = "SetCanvasSizeMessage";
}  // namespace MessageType

SetCanvasSizeMessage::SetCanvasSizeMessage(const int canvas_width_, const int canvas_height_)
  : canvas_width(canvas_width_), canvas_height(canvas_height_) {}

void to_json(nlohmann::json& json, const SetCanvasSizeMessage set_canvas_size_message) {
  json = nlohmann::json{};
  json["message_type"] = MessageType::SetCanvasSizeMessage;
  json["message_data"]["canvas_width"] = set_canvas_size_message.canvas_width;
  json["message_data"]["canvas_height"] = set_canvas_size_message.canvas_height;
}

}  // namespace cpp_web_viz
