#include "Grid.h"
#include "../AABB.h"
#include "../Player.h"
#include "../RNG.h"
#include "Cell.h"
#include "Enums.h"
#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <vector>
/* Grid */
Grid::Grid()
{
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cells[i][j].setCellCoords(i, j);
    }
  }
}

Grid::~Grid() { delete exitBox; }

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

Cell *Grid::getRandomCell()
{

  RNG rngEngine(1337);
  int row = rngEngine.getRandInt() % m;
  int col = rngEngine.getRandInt() % n;
  return &cells[row][col];
}

void Grid::initEntranceExit()
{
  entranceCell = getRandomCell();
  exitCell = getRandomCell();
  while (entranceCell == exitCell) {
    exitCell = getRandomCell();
  }

  exitBox = new AABB(
      glm::vec3(exitCell->getCell_x() + 0.2f, 0, exitCell->getCell_y() + 0.2f),
      glm::vec3(exitCell->getCell_x() + 0.8f, 1, exitCell->getCell_y() + 0.8f));

  std::cout << "Entrance cell: " << entranceCell->getCell_x() << ", "
            << entranceCell->getCell_y() << std::endl;
  std::cout << "Exit cell: " << exitCell->getCell_x() << ", "
            << exitCell->getCell_y() << std::endl;
}

bool Grid::isIntersectExit(Player *player)
{
  return exitBox->intersects(*(player->getCollisionBox()));
}

std::vector<float> Grid::buildMazeGeometry(std::vector<AABB *> &collisionBoxes)
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
      for (int k = 0; k < 4; k++) {
        if (cell->wallCollision[k]) {
          collisionBoxes.push_back(cell->wallCollision[k]);
        }
      }
    }
  }
  return vertices;
}
