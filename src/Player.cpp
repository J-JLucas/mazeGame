#define GLM_ENABLE_EXPERIMENTAL

#include "Player.h"
#include <GLFW/glfw3.h>
#include <glm/gtx/rotate_vector.hpp>

void Player::move(int GLFW_KEY, float deltaTime)
{
  float velocity = speed * deltaTime;
  float rotationSpeed = 160.0f;

  if (GLFW_KEY == GLFW_KEY_W) {
    position += getForwardVector() * velocity;
  }
  else if (GLFW_KEY == GLFW_KEY_S) {
    position -= getForwardVector() * velocity;
  }
  else if (GLFW_KEY == GLFW_KEY_A) {
    position -= getRightVector() * velocity;
  }
  else if (GLFW_KEY == GLFW_KEY_D) {
    position += getRightVector() * velocity;
  }
  else if (GLFW_KEY == GLFW_KEY_LEFT) {
    forward_vector = glm::rotate(
        forward_vector, glm::radians(rotationSpeed * deltaTime), getUpVector());
    right_vector = getRightVector();
  }
  else if (GLFW_KEY == GLFW_KEY_RIGHT) {
    forward_vector =
        glm::rotate(forward_vector, glm::radians(-rotationSpeed * deltaTime),
                    getUpVector());
    right_vector = getRightVector();
  }
}
