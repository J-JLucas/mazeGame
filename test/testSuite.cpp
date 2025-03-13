#include "../src/common.h"
#include "testWorldGen.h"
#include <glm/trigonometric.hpp>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main(int argc, char *argv[])
{
  unsigned int w = 1280;
  unsigned int h = 720;
  GLFWwindow *window = startup_opengl("TestSuite", w, h);
  if (!window) {
    return -1;
  }

  /* SHADERS */
  // Load shader source files
  std::string vertexShaderSource = loadShaderSource("../shaders/cube.vert");
  std::string fragmentShaderSource = loadShaderSource("../shaders/cube.frag");
  const char *vertexShaderSourceC = vertexShaderSource.c_str();
  const char *fragmentShaderSourceC = fragmentShaderSource.c_str();

  // Vertex Shader
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSourceC, NULL);
  glCompileShader(vertexShader);

  // Fragment Shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSourceC, NULL);
  glCompileShader(fragmentShader);

  // Shader Program
  unsigned int shaderProgram = glCreateProgram();

  // link compiled shaders to shader program
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // tell OpenGL to use our shader program
  glUseProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // get geometry from world generation
  std::vector<float> object_vertices = testWorldGeneration();
  std::vector<float> object_rgb;

  /*
  for (int i = 0; i < object_vertices.size(); i += 3) {
    object_rgb.push_back(0.0f);
    object_rgb.push_back(0.7f);
    object_rgb.push_back(0.35f);
  }
  */

  // 1)
  // Vertex Array Object (VAO)
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // 2)
  // Create Vertex Buffer Object (VBO)
  unsigned int VBO_points;
  glGenBuffers(1, &VBO_points);
  // bind VBO buffer to GL_ARRAY_BUFFER target (vertex array type)
  glBindBuffer(GL_ARRAY_BUFFER, VBO_points);

  // copy vertex data to bound GL_ARRAY_BUFFER (our VBO buffer)
  glBufferData(GL_ARRAY_BUFFER, object_vertices.size() * sizeof(float),
               object_vertices.data(), GL_STATIC_DRAW);

  // 3)
  // tell OpenGL how to interpret vertex data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0); // tell shader to turn on location 0 attribute

  // unsigned int VBO_colors;
  // glGenBuffers(1, &VBO_colors);
  // glBindBuffer(GL_ARRAY_BUFFER, VBO_colors);
  // glBufferData(GL_ARRAY_BUFFER, object_vertices.size() * sizeof(float),
  //              object_vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1); // tell shader to turn on location 1 attribute

  unsigned int mvpLocation = glGetUniformLocation(shaderProgram, "uMVP");

  float fov = 90.0f;
  float fovRad = glm::radians(fov);
  float aspect = static_cast<float>(w) / static_cast<float>(h);

  // Main Render Loop
  while (!glfwWindowShouldClose(window)) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }

    // For debugging: remove rotation from model transformation
    glm::mat4 model = glm::mat4(1.0f);

    glm::vec3 cameraPos = glm::vec3(9.0f, 4.0f, 5.0f);
    glm::vec3 cameraTarget = glm::vec3(5.0f, 0.0f, 5.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    // rotate camera to face north
    glm::vec3 direction = cameraPos - cameraTarget;
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f),
                                     glm::vec3(0.0f, 1.0f, 0.0f));
    direction = glm::vec3(rotation * glm::vec4(direction, 0.0f));
    cameraPos = cameraTarget + direction;

    glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, up);

    glm::mat4 projection =
        glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);

    glm::mat4 mvp = projection * view * model;
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));

    // Clear screen and depth buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the geometry
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, object_vertices.size() / 3);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
