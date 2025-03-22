/* Author: Josh Lucas
 * The map is represented by a discrete MxN grid of cells
 */
#pragma once

#include "Cell.h"
#include <vector>

class Grid {
private:
  static constexpr unsigned int m = 16;
  static constexpr unsigned int n = 16;
  Cell cells[m][n];

public:
  Grid()
  {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        cells[i][j].setCellCoords(i, j);
      }
    }
  }

  Cell *operator()(int i, int j);
  int getNumRows() { return m; }
  int getNumCols() { return n; }
  void printGridToConsole();
  std::vector<float> buildMazeGeometry(std::vector<AABB *> &collisionBoxes);
};
