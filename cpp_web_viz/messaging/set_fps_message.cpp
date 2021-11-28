#include <cpp_web_viz/messaging/set_fps_message.hpp>

namespace cpp_web_viz {

namespace MessageType {
  std::string SetFpsMessage = "SetFpsMessage";
}  // namespace MessageType

SetFpsMessage::SetFpsMessage(const Hz frames_per_second_)
  : frames_per_second(frames_per_second_) {}

void to_json(nlohmann::json& json, const SetFpsMessage set_fps_message) {
  json = nlohmann::json{};
  json["message_type"] = MessageType::SetFpsMessage;
  json["message_data"]["frames_per_second"] = set_fps_message.frames_per_second;
}

}  // namespace cpp_web_viz
