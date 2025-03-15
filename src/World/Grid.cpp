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

std::vector<float> Grid::buildMazeGeometry()
{
  // top left corner is (0, 0)
  // bottom right corner is (x = n, y = m)
  // each cell is a square of size scale
  std::vector<float> vertices;

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      Cell *cell = &cells[i][j];
      if (!cell) {
        continue;
      }

      cell->setCellCoords(i, j);
      cell->buildGeometry(vertices);
    }
  }
  // could generate entire ceiling as 2 triangles?
  /*
  vertices.push_back(0);
  vertices.push_back(0);
  vertices.push_back(0);

  vertices.push_back(n);
  vertices.push_back(0);
  vertices.push_back(0);

  vertices.push_back(0);
  vertices.push_back(0);
  vertices.push_back(m);

  vertices.push_back(n);
  vertices.push_back(0);
  vertices.push_back(m);

  vertices.push_back(n);
  vertices.push_back(0);
  vertices.push_back(0);

  vertices.push_back(0);
  vertices.push_back(0);
  vertices.push_back(m);
  */
  return vertices;
}
