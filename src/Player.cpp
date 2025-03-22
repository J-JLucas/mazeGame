#define GLM_ENABLE_EXPERIMENTAL

#include "Player.h"
#include "World/World.h"
#include <GLFW/glfw3.h>
#include <glm/gtx/rotate_vector.hpp>

void Player::move(int GLFW_KEY, float deltaTime)
{
  float velocity = speed * deltaTime;
  float rotationSpeed = 160.0f;

  world->printDebugPosition(this);

  if (GLFW_KEY == GLFW_KEY_W) {
    // position += getForwardVector() * velocity;
    position = world->validateMove(
        position, position + getForwardVector() * velocity, bounding_box);
    updateBoundingBox();
  }
  else if (GLFW_KEY == GLFW_KEY_S) {
    // position -= getForwardVector() * velocity;
    position = world->validateMove(
        position, position - getForwardVector() * velocity, bounding_box);
    updateBoundingBox();
  }
  else if (GLFW_KEY == GLFW_KEY_A) {
    // position -= getRightVector() * velocity;
    position = world->validateMove(
        position, position - getRightVector() * velocity, bounding_box);
    updateBoundingBox();
  }
  else if (GLFW_KEY == GLFW_KEY_D) {
    // position += getRightVector() * velocity;
    position = world->validateMove(
        position, position + getRightVector() * velocity, bounding_box);
    updateBoundingBox();
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

void Player::updateBoundingBox()
{
  bounding_box.min = position - glm::vec3(scale);
  bounding_box.max = position + glm::vec3(scale);
}
