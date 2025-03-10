cmake_minimum_required(VERSION 3.16)
# Use newer OpenGL policy to prefer GLVND when available
cmake_policy(SET CMP0072 NEW)

project(OpenGLPractice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find pkg-config, then check for GLFW and GLEW
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
pkg_check_modules(GLEW REQUIRED glew)

# Note: We do NOT use pkg_check_modules for glm because Arch's glm package
# doesn't provide a glm.pc file. Just install "glm" from pacman and include it.
# (Headers will be in /usr/include/glm)

# Include directories (OpenGL, GLFW, GLEW, plus system headers)
include_directories(
    ${OPENGL_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    /usr/include    # Typically redundant, but ensures GLM, etc.
)

# Create executable
#add_executable(mazeGame main.cpp)
add_executable(testSuite test/testSuite.cpp test/testWorldGen.cpp src/World/BinaryTreeMaze.cpp src/World/Cell.cpp src/World/Grid.cpp)

# Link libraries
#target_link_libraries(mazeGame
#    ${OPENGL_gl_LIBRARY}
#    ${GLFW_LIBRARIES}
#    ${GLEW_LIBRARIES}
#)

target_link_libraries(testSuite
    ${OPENGL_gl_LIBRARY}
    ${GLFW_LIBRARIES}
    ${GLEW_LIBRARIES}
)
