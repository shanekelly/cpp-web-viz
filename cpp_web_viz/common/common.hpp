#pragma once

#include <nlohmann/json.hpp>

namespace cpp_web_viz {

extern double NANOSECONDS_PER_SECOND;
extern double NANOSECONDS_PER_MILLISECOND;

using Hz = float;

using TimeInSeconds = float;

using TimeInMilliseconds = float;

struct Position
{
 public:
  Position(const float x_, const float y_);

  float x;
  float y;
};

struct PositionInMeters : public Position
{
};

struct PositionInPixels : public Position
{
 public:
  PositionInPixels();

  PositionInPixels(const float x_, const float y_);

  PositionInPixels operator+(const PositionInPixels& rhs) const;
};

/*
 * @brief - Converts to JSON. See https://github.com/nlohmann/json#arbitrary-types-conversions.
 */
void to_json(nlohmann::json& json, const PositionInPixels position);

struct Pose
{
 public:
  Pose(const PositionInMeters& position_);

  PositionInMeters position;
};

}  // namespace cpp_web_viz
