#include <cpp_web_viz/messaging/set_ping_message.hpp>

namespace cpp_web_viz {

namespace MessageType {
  std::string SetPingMessage = "SetPingMessage";
}  // namespace MessageType

SetPingMessage::SetPingMessage(const TimeInMilliseconds ping_)
  : ping(ping_) {}

void to_json(nlohmann::json& json, const SetPingMessage set_ping_message) {
  json = nlohmann::json{};
  json["message_type"] = MessageType::SetPingMessage;
  json["message_data"]["ping"] = set_ping_message.ping;
}

}  // namespace cpp_web_viz
