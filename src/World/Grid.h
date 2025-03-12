/* Author: Josh Lucas
 * The map is represented by a discrete MxN grid of cells
 */
#pragma once

#include "Cell.h"
#include <vector>

class Grid {
private:
  static constexpr unsigned int m = 8;
  static constexpr unsigned int n = 8;
  Cell cells[m][n];

public:
  Cell *operator()(int i, int j);
  int getNumRows() { return m; }
  int getNumCols() { return n; }
  void printGridToConsole();
  std::vector<float> buildMazeGeometry(unsigned int scaleFactor);
};
