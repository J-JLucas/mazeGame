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

void Cell::buildGeometry()
{

  /* FLOOR - 2 tri's, 4 vertices (2 shared) */
  // first triangle

  //   N
  // W   E
  //   S
  //
  // v1
  /*
  vertices.push_back(j); // x
  vertices.push_back(0); // y is vertical in opengl
  vertices.push_back(i); // z
  // v2
  vertices.push_back(j * scale);
  vertices.push_back(0);
  vertices.push_back(i);
  // v3
  vertices.push_back(j); // x
  vertices.push_back(0);
  vertices.push_back(i * scale);

  // second triangle
  // v4
  vertices.push_back(j * scale);
  vertices.push_back(0);
  vertices.push_back(i);
  // v3
  vertices.push_back(j); // x
  vertices.push_back(0);
  vertices.push_back(i * scale);
  // v2
  vertices.push_back(j * scale);
  vertices.push_back(0);
  vertices.push_back(i);
  */
}
