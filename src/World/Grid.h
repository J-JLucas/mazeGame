/* Author: Josh Lucas
 * The map is represented by a discrete MxN grid of cells
 */
#pragma once

#include "Cell.h"
#include <iostream>
#include <vector>

class Grid {
private:
  static constexpr unsigned int m = 3;
  static constexpr unsigned int n = 3;
  Cell cells[m][n];

  Cell *entranceCell;
  Cell *exitCell;
  AABB *exitBox;

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
  bool isIntersectExit(class Player *player);
  std::vector<float> buildMazeGeometry(std::vector<AABB *> &collisionBoxes);
};
