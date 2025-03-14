#pragma once

#include "Actor.h"
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>

class Player : public Actor {
private:
  float speed;

public:
  Player(glm::vec3 startPosition) : Actor(startPosition) { speed = 1.0f; }
  void setSpeed(unsigned int speed);
  int getSpeed();

  void handleInput(GLFWwindow *window, int key, int scancode, int action,
                   int mods);
  void bindInput(GLFWwindow *window);

  void move();
};
