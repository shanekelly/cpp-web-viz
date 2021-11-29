#pragma once

#include <string>

#include <nlohmann/json.hpp>

#include <cpp_web_viz/common/common.hpp>

namespace cpp_web_viz {

namespace MessageType {
  extern std::string SetPingMessage;
}  // namespace MessageType

class SetPingMessage
{
 public:
  SetPingMessage(const TimeInMilliseconds ping_);

  TimeInMilliseconds ping;
};

/*
 * @brief - Converts to JSON. See https://github.com/nlohmann/json#arbitrary-types-conversions.
 */
void to_json(nlohmann::json& json, const SetPingMessage set_ping_message);

}  // namespace cpp_web_viz
