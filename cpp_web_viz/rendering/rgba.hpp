#pragma once

#include <cstdint>

#include <nlohmann/json.hpp>

namespace cpp_web_viz {

struct RGBA {
 public:
  RGBA(const uint8_t r_, const uint8_t g_, const uint8_t b_, const float a_);

  uint8_t r;  // [0, 255]
  uint8_t g;  // [0, 255]
  uint8_t b;  // [0, 255]
  float a;  // [0, 1]
};

/*
 * @brief - Converts to JSON. See https://github.com/nlohmann/json#arbitrary-types-conversions.
 */
void to_json(nlohmann::json& json, const RGBA& rgba);

namespace Color {
  extern const RGBA Red;
}  // namespace color

}  // namespace cpp_web_viz
