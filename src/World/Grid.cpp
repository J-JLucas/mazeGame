#include "Grid.h"
#include "Cell.h"
#include "Enums.h"
#include <iostream>
#include <vector>
/* Grid */

// Access operator for cell object pointer at row, column
Cell *Grid::operator()(int row, int column)
{
  if (row < 0 || row >= m || column < 0 || column >= n) {
    return nullptr;
  }
  return &cells[row][column];
}

void Grid::printGridToConsole()
{
  const std::string body = "   ";
  const std::string hWall = "---";
  const char vWall = '|', corner = '+';

  // print northern most wall
  std::cout << corner;
  for (int i = 0; i < n; i++) {
    std::cout << hWall << corner;
  }
  std::cout << "\n";

  // print cell walls
  // for each row, build a 2 strings;
  // 1 for horizontal walls, 1 for vertical walls
  for (int i = 0; i < m; i++) {
    std::string top;    // represents the east walls
    std::string bottom; // represents the north walls
    top = top + vWall;
    bottom = bottom + corner;

    // add each cells wall info to the row strings
    for (int j = 0; j < n; j++) {
      Cell *cell = &cells[i][j];
      if (!cell) {
        continue;
      }
      top += body;
      top += cell->isWalled(Direction::EAST) ? "|" : " ";
      bottom += cell->isWalled(Direction::SOUTH) ? "---" : "   ";
      bottom += corner;
    }
    // print the wall row strings
    std::cout << top << "\n" << bottom << std::endl;
  }
}

std::vector<float> Grid::buildMazeGeometry(unsigned int scale)
{
  // top left corner is (0, 0)
  // bottom right corner is (n, m)
  // each cell is a square of size scale
  std::vector<float> vertices;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      Cell *cell = &cells[i][j];
      if (!cell) {
        continue;
      }

      /* FLOOR - 2 tri's, 4 vertices (2 shared) */
      // first triangle
      // v1
      vertices.push_back(j); // x
      vertices.push_back(0); // y is vertical in opengl
      vertices.push_back(i); // z
      // v2
      vertices.push_back(j + 1);
      vertices.push_back(0);
      vertices.push_back(i);
      // v3
      vertices.push_back(j); // x
      vertices.push_back(0);
      vertices.push_back(i + 1);

      // second triangle
      // v4
      vertices.push_back(j + 1);
      vertices.push_back(0);
      vertices.push_back(i + 1);
      // v3
      vertices.push_back(j);
      vertices.push_back(0);
      vertices.push_back(i + 1);
      // v2
      vertices.push_back(j + 1);
      vertices.push_back(0);
      vertices.push_back(i);
    }
  }
  return vertices;
}
