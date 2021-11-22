#pragma once

#include <chrono>
#include <string>

#include <nlohmann/json.hpp>

namespace cpp_web_viz {

namespace MessageType {
  extern std::string PingMessage;
}  // namespace MessageType

class PingMessage
{
 public:
  PingMessage();

  PingMessage(const std::chrono::nanoseconds& sent_timestamp_);

  std::chrono::nanoseconds sent_timestamp;
};

/*
 * @brief - Converts from JSON. See https://github.com/nlohmann/json#arbitrary-types-conversions.
 */
void from_json(const nlohmann::json& json, PingMessage& ping_message);

/*
 * @brief - Converts to JSON. See https://github.com/nlohmann/json#arbitrary-types-conversions.
 */
void to_json(nlohmann::json& json, const PingMessage ping_message);

}  // namespace cpp_web_viz
