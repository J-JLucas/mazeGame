/* Author: Josh Lucas
 * The map is represented by a discrete MxN grid of cells
 */
#pragma once

#include "Cell.h"
#include <iostream>
#include <vector>

class Grid {
private:
  static constexpr unsigned int m = 16;
  static constexpr unsigned int n = 16;
  Cell cells[m][n];

  Cell *exitCell;

public:
  Grid();
  Cell *operator()(int i, int j);
  int getNumRows() { return m; }
  int getNumCols() { return n; }
  Cell *getRandomCell();
  void printGridToConsole();
  std::vector<float> buildMazeGeometry(std::vector<AABB *> &collisionBoxes);
};
