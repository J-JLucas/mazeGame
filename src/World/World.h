#pragma once

#include "Grid.h"
#include <glm/ext/vector_float3.hpp>
#include <vector>

class World {
private:
  Grid gridMap;

public:
  std::vector<float> generateWorld();
  glm::vec3 validateMove(glm::vec3 old_pos, glm::vec3 new_pos);
};
