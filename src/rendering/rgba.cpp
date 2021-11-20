#include "rendering/rgba.hpp"

namespace sw {

RGBA::RGBA(const uint8_t r_, const uint8_t g_, const uint8_t b_, const float a_)
  : r(r_), g(g_), b(b_), a(a_) {}

void to_json(nlohmann::json& json, const RGBA& rgba) {
  json = nlohmann::json{
    {"r", rgba.r},
    {"g", rgba.g},
    {"b", rgba.b},
    {"a", rgba.a}};
}

}  // namespace sw
