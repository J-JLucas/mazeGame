#pragma once

// enum for 4 cardinal directions
enum class Direction { NORTH, EAST, SOUTH, WEST };
inline Direction opposite(Direction d)
{
  switch (d) {
  case Direction::NORTH:
    return Direction::SOUTH;
  case Direction::EAST:
    return Direction::WEST;
  case Direction::SOUTH:
    return Direction::NORTH;
  case Direction::WEST:
    return Direction::EAST;
  }
}
