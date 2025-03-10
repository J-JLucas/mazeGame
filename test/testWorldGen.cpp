#include "testWorldGen.h"
#include "../src/World/BinaryTreeMaze.h"
#include "../src/World/Grid.h"
#include <iostream>

void testWorldGeneration()
{
  Grid map;
  BinaryTreeMaze::generateMaze(map);
  map.printGridToConsole();

  std::cout << "World Generation Test Passed." << std::endl;
}
