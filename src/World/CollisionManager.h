/* Collision Manager is a singleton
 * who tracks all collision boxes in a given world
 * (world must register each instance of CollisionBox)
 * and checks for collisions between the player and each box
 * simple implementation, should just be called every tick
 * of game loop
 */

#pragma once

#include <vector>

class CollisionManager {
private:
  std::vector<class CollisionBox *> collisionBoxes;

public:
  void registerBox(CollisionBox *box);
  void checkCollisions(CollisionBox *playerBox);
};
