/* Author: Josh Lucas
 * The map is represented by a discrete MxN grid of cells
 */
#pragma once

#include "Cell.h"
#include <iostream>
#include <vector>

class Grid {
private:
  static constexpr unsigned int m = 8;
  static constexpr unsigned int n = 8;
  Cell cells[m][n];

  Cell *entranceCell;
  Cell *exitCell;

public:
  Grid();
  ~Grid();
  Cell *operator()(int i, int j);
  int getNumRows() { return m; }
  int getNumCols() { return n; }
  Cell *getRandomCell();
  void printGridToConsole();
  void initEntranceExit();
  Cell *getEntranceCell() { return entranceCell; }
  Cell *getExitCell() { return exitCell; }
  std::vector<float> buildMazeGeometry(std::vector<AABB *> &collisionBoxes);
};
