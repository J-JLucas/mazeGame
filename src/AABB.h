/*
 * Simple Axis Aligned Bounding Box class
 * min and max are the back bottom left and front upper right corners of the
 * bounding box
 *
 * coordinate system in this game:
 *      -z
 *  -x __|__ +x
 *       |
 *      +z
 *
 *  AABB:
 *       +_________+
 *      /|        /|
 *     +_________+max
 *     | |       | |
 *    min+_______|_+
 *     |/        |/
 *     +_________+
 *
 * https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
 */

#pragma once

#include <glm/glm.hpp>
#include <iostream>

class AABB {

public:
  glm::vec3 min;
  glm::vec3 max;

  AABB(glm::vec3 min, glm::vec3 max) : min(min), max(max) {}

  bool intersects_x_axis(const AABB &other) const
  {
    if (max.x < other.min.x || min.x > other.max.x)
      return false;
    std::cout << "Intersects x axis" << std::endl;
    std::cout << "min.x: " << min.x << " max.x: " << max.x
              << " other.min.x: " << other.min.x
              << " other.max.x: " << other.max.x << std::endl;

    return true;
  }

  bool intersects_y_axis(const AABB &other) const
  {
    if (max.y < other.min.y || min.y > other.max.y)
      return false;
    std::cout << "Intersects y axis" << std::endl;
    return true;
  }

  bool intersects_z_axis(const AABB &other) const
  {
    if (max.z < other.min.z || min.z > other.max.z)
      return false;

    std::cout << "Intersects z axis" << std::endl;
    std::cout << "min.z: " << min.z << " max.z: " << max.z
              << " other.min.z: " << other.min.z
              << " other.max.z: " << other.max.z << std::endl;

    return true;
  }
  bool intersects(const AABB &other) const
  {
    return intersects_x_axis(other) && intersects_z_axis(other);
  }
};
