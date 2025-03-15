#pragma once

// We live in a 2D world projected into 3D space
// so we can use a rectangular plane instead of a full
// 3D box for collision detection

class CollisionBox {
public:
  float x_min;
  float x_max;
  float z_min;
  float z_max;
  float width;

  float y = 0.5;

  CollisionBox(float x_min, float x_max, float z_min, float z_max, float width)
      : x_min(x_min), x_max(x_max), z_min(z_min), z_max(z_max), width(width) {};

  bool isColliding(CollisionBox *otherBox);
};
