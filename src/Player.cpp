#include "Player.h"
#include <utility>

/*
void Player::bindInput(GLFWwindow *window)
{
  glfwSetKeyCallback(window, handleInput);
}
*/

void Player::handleInput(GLFWwindow *window, int key, int scancode, int action,
                         int mods)
{
  //
  // Handle keyboard input for movement
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    position += forward_vector * speed; // * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    position -= forward_vector * speed; // * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    position -= right_vector * speed; // * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    position += right_vector * speed; // * deltaTime;

  /*
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
    // Rotate left (counterclockwise around worldUp)
    forward_vector = glm::rotate(
        cameraDirection, glm::radians(rotationSpeed * deltaTime), worldUp);
    right = glm::normalize(glm::cross(cameraDirection, worldUp));
  }
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    // Rotate right (clockwise around worldUp)
    cameraDirection = glm::rotate(
        cameraDirection, glm::radians(-rotationSpeed * deltaTime), worldUp);
    right = glm::normalize(glm::cross(cameraDirection, worldUp));
  }
  */
}
