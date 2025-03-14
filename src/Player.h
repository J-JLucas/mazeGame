#pragma once

#include "Actor.h"
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>

class Player : public Actor {
private:
  float speed;

public:
  Player(glm::vec3 startPosition) : Actor(startPosition) { speed = 3.0f; }
  void setSpeed(unsigned int speed);
  float getSpeed();
  void move(int GLFW_KEY, float deltaTime);
};
