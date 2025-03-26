#include "SidewinderMaze.h"
#include "../../RNG.h"
#include "../Cell.h"
#include "../Enums.h"
#include "../Grid.h"
#include <vector>

/* Sidewinder Maze Generation Algie
 * As the Sidewinder Algie moves through the grid,
 * for each row, we maintain a "cluster" of cells.
 * for each cell, we add the cell to the cluster and "flip a coin",
 * if tails we link the cell east and continue
 * if heads we choose a random cell from the cluster and link it to it's
 * northern neighbor, then clear the cluster and continue
 */

void SidewinderMaze::generateMaze(Grid &grid)
{
  RNG rngEngine(1337);
  int m = grid.getNumRows();
  int n = grid.getNumCols();

  for (int i = 0; i < m; i++) {
    std::vector<Cell *> cluster;

    for (int j = 0; j < n; j++) {
      if ((i == 0) && (j == n - 1)) {
        // top right corner, do nothing
        continue;
      }
      else if (i == 0) {
        // link east; we're along north wall
        grid(i, j)->link(Direction::EAST, grid(i, j + 1));
      }
      else {
        // add cell to cluster
        cluster.push_back(grid(i, j));

        // flip coin
        int r = rngEngine.getRandInt() % 2;

        if (r || (j == n - 1)) {
          // heads or are at the east wall and must go north
          int random = rngEngine.getRandInt() % cluster.size();
          int row = cluster[random]->getCell_y();
          int col = cluster[random]->getCell_x();
          cluster[random]->link(
              Direction::NORTH,
              grid(row - 1, col)); // link random cell to it's northern neighbor
          cluster.clear();
        }
        else {
          // tails
          grid(i, j)->link(Direction::EAST, grid(i, j + 1));
        }
      }
    }
  }
}
