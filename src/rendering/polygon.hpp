#pragma once

#include "nlohmann/json.hpp"

#include "common/common.hpp"
#include "rendering/rgba.hpp"

namespace cpp_web_viz {

class Polygon {
 public:
  Polygon();

  Polygon(const std::vector<PositionInPixels>& vertices_, const RGBA& edge_color_,
          const RGBA& fill_color_);

  void Translate(const PositionInPixels& t);

  std::vector<PositionInPixels> vertices;  // CCW vertices.
  RGBA edge_color;  // The color of the edges of the polygon.
  RGBA fill_color;  // The color of the inside of the polygon.
};

/*
 * @brief - Converts to JSON. See https://github.com/nlohmann/json#arbitrary-types-conversions.
 */
void to_json(nlohmann::json& json, const Polygon& polygon);

}  // namespace cpp_web_viz
