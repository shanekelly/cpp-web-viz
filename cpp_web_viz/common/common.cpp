#include <cpp_web_viz/common/common.hpp>

namespace cpp_web_viz {

double NANOSECONDS_PER_SECOND = 1e9;
double NANOSECONDS_PER_MILLISECOND = 1e6;

Position::Position(const float x_, const float y_) : x(x_), y(y_) {}

PositionInPixels::PositionInPixels()
  : Position(0, 0)
{
}

PositionInPixels::PositionInPixels(const float x_, const float y_)
  : Position(x_, y_) {}

PositionInPixels PositionInPixels::operator+(const PositionInPixels& rhs) const {
  return PositionInPixels{x + rhs.x, y + rhs.y};
}

void to_json(nlohmann::json& json, const PositionInPixels position) {
  json = nlohmann::json{
    {"x", position.x},
    {"y", position.y}};
}

Pose::Pose(const PositionInMeters& position_) : position(position_) {}

}  // namespace cpp_web_viz
