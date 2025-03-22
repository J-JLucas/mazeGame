#include "World.h"
#include "../Player.h"
// #include "mazeAlgies/BinaryTreeMaze.h"
#include "mazeAlgies/SidewinderMaze.h"
#include <glm/ext/vector_float3.hpp>
#include <iomanip>
#include <iostream>
#include <vector>

std::vector<float> World::generateWorld()
{
  // Carve out the maze in the gridmap
  // BinaryTreeMaze::generateMaze(gridMap);
  SidewinderMaze::generateMaze(gridMap);
  gridMap.printGridToConsole();

  // Generate Maze 3D Geometry
  std::vector<float> verts = gridMap.buildMazeGeometry(collisionBoxes);
  return verts;
}

glm::vec3 World::validateMove(glm::vec3 old_pos, glm::vec3 new_pos,
                              AABB &player_box)
{
  for (auto &box : collisionBoxes) {
    if (box->intersects(player_box)) {
      std::cout << "****COLLISION DETECTED****" << std::endl;

      // We resolve axis with the smallest penetration for least jarring
      // correction
      float overlapX = std::min(player_box.max.x, box->max.x) -
                       std::max(player_box.min.x, box->min.x);
      float overlapZ = std::min(player_box.max.z, box->max.z) -
                       std::max(player_box.min.z, box->min.z);

      // 1) Determine which side of the other box the player is on
      // 2) push player player out the opposite direction of the overlap
      if (overlapX < overlapZ) {
        if (player_box.min.x < box->min.x)
          new_pos.x -= overlapX;
        else
          new_pos.x += overlapX;
      }
      else {
        if (player_box.min.z < box->min.z)
          new_pos.z -= overlapZ;
        else
          new_pos.z += overlapZ;
      }
    }
  }
  return new_pos;
}

void World::registerCollision(AABB &box) { collisionBoxes.push_back(&box); }

void World::printDebugPosition(Player *player)
{
  if (!player) {
    return;
  }

  glm::vec3 player_pos = player->getPosition();

  int cell_x = static_cast<int>(player_pos.x);
  int cell_z = static_cast<int>(player_pos.z);
  int n = -1;
  int e = -1;
  int s = -1;
  int w = -1;

  Cell *cell = gridMap(cell_z, cell_x);
  if (cell) {
    n = cell->isWalled(Direction::NORTH) ? 1 : 0;
    e = cell->isWalled(Direction::EAST) ? 1 : 0;
    s = cell->isWalled(Direction::SOUTH) ? 1 : 0;
    w = cell->isWalled(Direction::WEST) ? 1 : 0;
  }

  std::cout << std::fixed << std::setprecision(2);
  std::cout << " position (" << player_pos.x << ", " << player_pos.z
            << ") cell (" << cell_x << ", " << cell_z << ") walls (" << n
            << ", " << e << ", " << s << ", " << w << ")" << std::endl;
}
