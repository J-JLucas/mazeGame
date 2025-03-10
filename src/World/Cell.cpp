#include "Cell.h"
#include "Enums.h"

/* Cell */
void Cell::link(Direction d, Cell *neighbor, bool bidirectional)
{
  // Open the wall in this cell
  walls[static_cast<int>(d)] = false;

  if (bidirectional) {
    // Open the opposite wall in the neighboring cell
    neighbor->link(opposite(d), this, false);
  }
}

void Cell::unlink(Direction d, Cell *neighbor, bool bidirectional)
{
  walls[static_cast<int>(d)] = true;
  if (bidirectional) {
    // unlink other cell from this
    neighbor->unlink(opposite(d), this, false);
  }
}
