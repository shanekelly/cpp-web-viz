#include <cpp_web_viz/messaging/ping_message.hpp>

namespace cpp_web_viz {

namespace MessageType {
  std::string PingMessage = "PingMessage";
}  // namespace MessageType

PingMessage::PingMessage()
  : sent_timestamp(0)
{
}

PingMessage::PingMessage(const std::chrono::nanoseconds& sent_timestamp_)
  : sent_timestamp(sent_timestamp_)
{
}

void from_json(const nlohmann::json& json, PingMessage& ping_message)
{
  ping_message.sent_timestamp =
    std::chrono::nanoseconds(json.at("message_data").at("sent_timestamp"));
}

void to_json(nlohmann::json& json, const PingMessage ping_message)
{
  json = nlohmann::json{};
  json["message_type"] = MessageType::PingMessage;
  json["message_data"]["sent_timestamp"] = ping_message.sent_timestamp.count();
}

}  // namespace cpp_web_viz
