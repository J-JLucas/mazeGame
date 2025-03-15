#pragma once

#include "Actor.h"
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>

class Player : public Actor {
private:
  float speed;
  class World *world;

public:
  Player(World *world, glm::vec3 startPosition)
      : world(world), Actor(startPosition)
  {
    speed = 2.0f;
  }
  void setSpeed(unsigned int speed);
  float getSpeed();
  void move(int GLFW_KEY, float deltaTime);
};
