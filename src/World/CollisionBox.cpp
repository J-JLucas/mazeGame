#include "CollisionBox.h"

bool CollisionBox::isColliding(CollisionBox *other)
{
  // Check if the two boxes are colliding
  // Return true if they are, false otherwise

  // x

  // THIS IS ISN'T GOING TO WORK
  //  WHEN THE PLAYER ROTATES, THEIR X MIN AND Z WILL
  //  CHANGE, NEED TO MORE ROBUST SOLUTION
  /*
  if (x_min < other->x_max && x_max > other->x_min)
  {
    // z
    if (z_min < other->z_max && z_max > other->z_min)
    {
      return true;
    }
  }
  */

  return false;
}
