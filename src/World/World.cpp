#include "World.h"
#include "BinaryTreeMaze.h"
#include <glm/ext/vector_float3.hpp>
#include <vector>

std::vector<float> World::generateWorld()
{
  // Carve out the maze in the gridmap
  BinaryTreeMaze::generateMaze(gridMap);
  gridMap.printGridToConsole();

  // Generate Maze 3D Geometry
  std::vector<float> verts = gridMap.buildMazeGeometry();
  return verts;
}

glm::vec3 World::validateMove(glm::vec3 old_pos, glm::vec3 new_pos)
{
  int old_pos_x = static_cast<int>(old_pos.x);
  int old_pos_z = static_cast<int>(old_pos.z);

  int new_pos_x = static_cast<int>(new_pos.x + 0.2f);
  int new_pos_z = static_cast<int>(new_pos.z + 0.2f);

  // didn't leave current cell
  if (new_pos_x == old_pos_x && new_pos_z == old_pos_z) {
    return new_pos;
  }

  Cell *old_cell = gridMap(old_pos_z, old_pos_x);
  Cell *new_cell = gridMap(new_pos_z, new_pos_x);
  if (!new_cell) {
    return old_pos;
  }

  if (new_pos_x > old_pos_x) {
    if (old_cell->isWalled(Direction::EAST)) {
      return old_pos;
    }
  }
  else if (new_pos_x < old_pos_x) {
    if (old_cell->isWalled(Direction::WEST)) {
      return old_pos;
    }
  }
  else if (new_pos_z > old_pos_z) {
    if (old_cell->isWalled(Direction::SOUTH)) {
      return old_pos;
    }
  }
  else if (new_pos_z < old_pos_z) {
    if (old_cell->isWalled(Direction::NORTH)) {
      return old_pos;
    }
  }

  return new_pos;
}
