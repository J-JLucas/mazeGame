#include "testWorldGen.h"
#include "../src/World/BinaryTreeMaze.h"
#include "../src/World/Grid.h"
#include <iostream>
#include <vector>
std::vector<float> testWorldGeneration()
{

  // Create a world
  Grid map;
  BinaryTreeMaze::generateMaze(map);
  map.printGridToConsole();
  std::vector<float> verts = map.buildMazeGeometry(100);

  std::cout << "World Generation Test Passed." << std::endl;

  return verts;
}
