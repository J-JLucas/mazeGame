#include "common.h"
int main()
{
  unsigned int w = 1280;
  unsigned int h = 720;
  GLFWwindow *window = startup_opengl("MazeGame", w, h);
  if (!window) {
    return -1;
  }

  /* SHADERS */
  // Load shader source files
  std::string vertexShaderSource = loadShaderSource("../shaders/basic.vert");
  std::string fragmentShaderSource = loadShaderSource("../shaders/basic.frag");
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
  // glBufferData(GL_ARRAY_BUFFER, sizeof(object_vertices), object_vertices,
  // GL_STATIC_DRAW);

  // 3)
  // tell OpenGL how to interpret vertex data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0); // tell shader to turn on location 0 attribute

  unsigned int VBO_colors;
  glGenBuffers(1, &VBO_colors);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_colors);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(object_rbg), object_rgb,
  //              GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  // glEnableVertexAttribArray(1); // tell shader to turn on location 1
  // attribute

  // Main Render Loop
  while (!glfwWindowShouldClose(window)) {

    // terminate on ESC key press
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }

    // Clear the screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw to double buffer
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    // glDrawArrays(GL_LINE_LOOP, 0, 3);

    // check for events and swap buffers, rendering triangle to screen
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
