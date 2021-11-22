#pragma once

#include <string>

#include <nlohmann/json.hpp>

namespace cpp_web_viz {

namespace MessageType {
  extern std::string SetCanvasSizeMessage;
}  // namespace MessageType

class SetCanvasSizeMessage
{
 public:
  SetCanvasSizeMessage(const int canvas_width_, const int canvas_height_);

  int canvas_width;
  int canvas_height;
};

/*
 * @brief - Converts to JSON. See https://github.com/nlohmann/json#arbitrary-types-conversions.
 */
void to_json(nlohmann::json& json, const SetCanvasSizeMessage set_canvas_size_message);

}  // namespace cpp_web_viz
