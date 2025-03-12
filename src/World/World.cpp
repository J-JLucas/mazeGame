#include "World.h"
#include "BinaryTreeMaze.h"

void World::generateWorld()
{
  // Carve out the maze in the gridmap
  BinaryTreeMaze::generateMaze(gridMap);
  gridMap.printGridToConsole();

  // Generate Maze 3D Geometry
  std::vector<float> verts = gridMap.buildMazeGeometry(100);
}
