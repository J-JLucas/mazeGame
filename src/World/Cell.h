/* Author: Josh Lucas
 * cells are the elements that makeup the gridmap;
 */
#pragma once

#include "Enums.h"
#include <cmath>
#include <vector>

class Cell {
private:
  // cell coords
  int i, j;
  float collisionWidth = .1f;
  // used to determine if a wall exists in that direction from center of cell
  // default state walls are closed, generation algies will carve out openings
  // 0 = opening, 1 = wall
  bool walls[4] = {true, true, true, true};

public:
  ~Cell();

  void setCellCoords(int i, int j)
  {
    this->i = i;
    this->j = j;
  }
  int getCell_x() const { return j; }
  int getCell_y() const { return i; }
  bool isWalled(Direction d) { return walls[static_cast<int>(d)]; }
  class AABB *wallCollision[4] = {nullptr, nullptr, nullptr, nullptr};

  void link(Direction d, Cell *neighbor, bool bidirectional = true);
  void unlink(Direction d, Cell *neighbor, bool bidirectional = true);
  void buildGeometry(std::vector<float> &vertices);
};
