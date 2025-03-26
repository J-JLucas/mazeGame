
#pragma once

#include <random>
class RNG {
  std::mt19937 rng;
  std::uniform_int_distribution<> distribution;

public:
  RNG(int n) : rng(std::random_device{}())
  {
    distribution = std::uniform_int_distribution<>(0, n);
  }

  int getRandInt() { return distribution(rng); }
};
