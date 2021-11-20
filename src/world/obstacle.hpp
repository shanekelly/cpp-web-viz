#include "common/common.hpp"

class Obstacle
{
 public:
   Obstacle(const std::vector<PositionInMeters>& vertices_) : vertices(vertices_) {}

   std::vector<PositionInMeters> vertices;
};
