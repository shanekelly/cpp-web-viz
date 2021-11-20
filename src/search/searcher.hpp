#include "common/common.hpp"
#include "world/obstacle.hpp"
#include "world/path.hpp"

class Searcher
{
 public:
  /**
   * @brief - Runs only once for each search problem to set up necessary intermediate data
   * structures, such as the costmap.
   * @param obstacles - The obstacles to avoid during path searching.
   */
  virtual void SetUpSearchProblem(const std::vector<Obstacle>& obstacles) = 0;

  /**
   * @brief - Can be run many times to update the start position, goal positions, or obstacles to
   * efficiently compute a new path.
   * @param start - The ego starting pose to search from.
   * @param goal - The goal pose to search to.
   * @param obstacles - The obstacles to avoid during path searching.
   * @returns - A (hopefully optimal) path from the start to the goal.
   */
  virtual Path SolveSearchProblem(
    const Pose& start, const Pose& goal, const std::vector<Obstacle>& obstacles) = 0;
};
