#pragma once

#include "AABB.h"
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>

class Actor {
protected:
  glm::vec3 position; // (x,y,z)

  // unit vectors; all actors face South by default
  glm::vec3 forward_vector;
  glm::vec3 right_vector;
  glm::vec3 up_vector;
  AABB bounding_box;
  float scale;

public:
  Actor(glm::vec3 startPosition, float scale)
      : position(startPosition), scale(scale),
        bounding_box(startPosition - glm::vec3(scale),
                     startPosition + glm::vec3(scale))
  {
    forward_vector = glm::vec3(0.0f, 0.0f, 1.0f);
    up_vector = glm::vec3(0.0f, 1.0f, 0.0f);
    right_vector = getRightVector();
  }

  glm::vec3 getPosition() { return position; }

  // forward vector changes by rotatation about the y-axis
  glm::vec3 getForwardVector() { return forward_vector; }

  // player can't tilt up or down, should remain constant
  glm::vec3 getUpVector() { return up_vector; }

  // computed via cross product of forward and up vectors
  glm::vec3 getRightVector()
  {
    return glm::normalize(glm::cross(forward_vector, up_vector));
  }
};
