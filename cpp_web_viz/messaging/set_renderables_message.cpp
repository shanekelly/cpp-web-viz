#include <cpp_web_viz/messaging/set_renderables_message.hpp>

namespace cpp_web_viz {

namespace MessageType {
  std::string SetRenderablesMessage = "SetRenderablesMessage";
}  // namespace MessageType

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

}  // namespace cpp_web_viz
