#include "CollisionManager.h"
#include "CollisionBox.h"

void CollisionManager::registerBox(CollisionBox *box)
{
  collisionBoxes.push_back(box);
}

void CollisionManager::checkCollisions(CollisionBox *playerBox)
{
  for (auto box : collisionBoxes) {
    // check if player_pos is within box
    // if so, do something
  }
}
