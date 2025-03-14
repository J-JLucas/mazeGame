
#include <iomanip>
#define GLM_ENABLE_EXPERIMENTAL

#include "../src/common.h"
#include "testWorldGen.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/trigonometric.hpp>
#include <vector>

#include "../src/Player.h"
int main(int argc, char *argv[])
{
  unsigned int w = 1280;
  unsigned int h = 720;
  GLFWwindow *window = startup_opengl("TestSuite", w, h);
  if (!window) {
    return -1;
  }

  // SHADERS
  std::string vertexShaderSource = loadShaderSource("../shaders/cube.vert");
  std::string fragmentShaderSource = loadShaderSource("../shaders/cube.frag");
  const char *vertexShaderSourceC = vertexShaderSource.c_str();
  const char *fragmentShaderSourceC = fragmentShaderSource.c_str();

  // Create and compile vertex shader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSourceC, NULL);
  glCompileShader(vertexShader);

  // Create and compile fragment shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSourceC, NULL);
  glCompileShader(fragmentShader);

  // Link shaders to shader program
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // Get geometry from world generation
  std::vector<float> object_vertices = testWorldGeneration();
  Player player = Player(glm::vec3(0.5f, 0.5f, -3.0f));

  // Vertex Array Object (VAO)
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // Create Vertex Buffer Object (VBO) and send vertex data to GPU
  unsigned int VBO_points;
  glGenBuffers(1, &VBO_points);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_points);
  glBufferData(GL_ARRAY_BUFFER, object_vertices.size() * sizeof(float),
               object_vertices.data(), GL_STATIC_DRAW);

  // Set up vertex attributes for positions (location 0) and colors (location 1)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Get the uniform location for the MVP matrix in the shader
  unsigned int mvpLocation = glGetUniformLocation(shaderProgram, "uMVP");

  // Setup projection parameters
  float fov = 90.0f;
  float aspect = static_cast<float>(w) / static_cast<float>(h);

  // Set up initial camera parameters

  // glm::vec3 cameraPos(0.5f, 0.5f, -3.0f);
  glm::vec3 cameraPos = player.getPosition();
  // glm::vec3 cameraTarget = cameraPos + glm::vec3(0.0f, 0.0f, 1.0f);

  // glm::vec3 cameraTarget(0.0f, 0.5f, 0.0f);
  // Calculate fixed forward (view) direction
  // glm::vec3 cameraDirection = glm::normalize(cameraTarget - cameraPos);
  glm::vec3 cameraDirection = player.getForwardVector();

  glm::vec3 worldUp = player.getUpVector();
  // glm::vec3 right = glm::normalize(glm::cross(cameraDirection, worldUp));
  glm::vec3 right = player.getRightVector();

  /*
  glm::vec3 cameraPos = player.getPosition();
  glm::vec3 cameraDirection = player.getForwardVector();
  glm::vec3 worldUp = player.getUpVector();
  glm::vec3 right = player.getRightVector();
*/

  // Timing for smooth movement
  float lastFrameTime = glfwGetTime();
  float movementSpeed = 3.0f; // units per second
  float rotationSpeed = 90.0f;

  // Main Render Loop
  while (!glfwWindowShouldClose(window)) {
    // Check if the escape key was pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Position: (" << cameraPos.x << ", " << cameraPos.y << ", "
              << cameraPos.z << ")" << std::endl;

    // Compute delta time
    float currentFrameTime = glfwGetTime();
    float deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;

    // Handle keyboard input for movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      cameraPos += cameraDirection * movementSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      cameraPos -= cameraDirection * movementSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      cameraPos -= right * movementSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      cameraPos += right * movementSpeed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
      // Rotate left (counterclockwise around worldUp)
      cameraDirection = glm::rotate(
          cameraDirection, glm::radians(rotationSpeed * deltaTime), worldUp);
      right = glm::normalize(glm::cross(cameraDirection, worldUp));
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
      // Rotate right (clockwise around worldUp)
      cameraDirection = glm::rotate(
          cameraDirection, glm::radians(-rotationSpeed * deltaTime), worldUp);
      right = glm::normalize(glm::cross(cameraDirection, worldUp));
    }

    // Compute the view matrix using the updated camera position
    glm::mat4 view =
        glm::lookAt(cameraPos, cameraPos + cameraDirection, worldUp);
    glm::mat4 projection =
        glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp = projection * view * model;
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));

    // Clear the screen and depth buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the geometry
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, object_vertices.size() / 3);
    glBindVertexArray(0);

    // Set the desired line thickness (e.g., 5.0 pixels)
    glLineWidth(5.0f);
    // Begin drawing lines
    glBegin(GL_LINES);
    // X-axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);

    // Y-axis in green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);

    // Z-axis in blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();

    // Swap buffers and poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
