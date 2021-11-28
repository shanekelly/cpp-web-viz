#pragma once

#include <string>

#include <nlohmann/json.hpp>

#include <cpp_web_viz/common/common.hpp>

namespace cpp_web_viz {

namespace MessageType {
  extern std::string SetFpsMessage;
}  // namespace MessageType

class SetFpsMessage
{
 public:
  SetFpsMessage(const Hz frames_per_second_);

  Hz frames_per_second;
};

/*
 * @brief - Converts to JSON. See https://github.com/nlohmann/json#arbitrary-types-conversions.
 */
void to_json(nlohmann::json& json, const SetFpsMessage set_fps_message);

}  // namespace cpp_web_viz
