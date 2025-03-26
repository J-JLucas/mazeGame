#pragma once

#include "Grid.h"
#include <glm/ext/vector_float3.hpp>
#include <vector>

class World {
private:
  Grid gridMap;
  std::vector<AABB *> collisionBoxes;

public:
  std::vector<float> generateWorld();
  glm::vec3 validateMove(glm::vec3 old_pos, glm::vec3 new_pos,
                         AABB &player_box);
  bool reachedExit(class Player *player);
  void registerCollision(AABB &box);
  void printDebugPosition(class Player *player);
};
