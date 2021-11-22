#pragma once

#include <nlohmann/json.hpp>

#include <cpp_web_viz/common/common.hpp>
#include <cpp_web_viz/rendering/rgba.hpp>

namespace cpp_web_viz {

class Circle {
 public:
  Circle();

  Circle(const PositionInPixels& position_, const float radius_, const RGBA& edge_color_,
    const RGBA& fill_color_);

  void Translate(const PositionInPixels& t);

  PositionInPixels position;  // The position of the center of the circle.
  float radius;
  RGBA edge_color;  // The color of the edges of the circle.
  RGBA fill_color;  // The color of the inside of the circle.
};

/*
 * @brief - Converts to JSON. See https://github.com/nlohmann/json#arbitrary-types-conversions.
 */
void to_json(nlohmann::json& json, const Circle& circle);

}  // namespace cpp_web_viz
