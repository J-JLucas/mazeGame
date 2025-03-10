#include "BinaryTreeMaze.h"
#include "../common.h"
#include "Cell.h"
#include "Enums.h"
#include "Grid.h"

/* Binary Tree Maze Generation Algie
 * We're going to step through each cell in the grid 1 by 1
 * and carve an opening either to the north or east
 * linking two neighboring cells together
 */

void BinaryTreeMaze::generateMaze(Grid &grid)
{
  RNG rngEngine(1337);
  int m = grid.getNumRows();
  int n = grid.getNumCols();

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if ((i == 0) && (j == n - 1)) {
        // top right corner, do nothing
        continue;
      }
      else if (i == 0) {
        // link east; we're along north wall
        grid(i, j)->link(Direction::EAST, grid(i, j + 1));
      }
      else if (j == n - 1) {
        // link north; we're along east wall
        grid(i, j)->link(Direction::NORTH, grid(i - 1, j));
      }
      else {
        // random choice between north and east
        int r = rngEngine.getRandInt() % 2;
        if (r) {
          grid(i, j)->link(Direction::NORTH, grid(i - 1, j));
        }
        else {
          grid(i, j)->link(Direction::EAST, grid(i, j + 1));
        }
      }
    }
  }
}
