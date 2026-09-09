// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_ANIMATION_H_
#define INCLUDE_PANO_ANIMATION_H_

#include <chrono>

namespace Pano {
class Animation {
 public:
  Animation() {}
  ~Animation() {}

  Animation(const Animation&) = delete;
  Animation& operator=(const Animation&) = delete;
  Animation(Animation&&) = delete;
  Animation& operator=(Animation&&) = delete;

  /*
  Called to perform a single frame at the given timestamp.
  Returns true if the animation has more frames.
  */
  virtual bool Tick(const std::chrono::system_clock::time_point) = 0;
};
};  // namespace Pano

#endif  // INCLUDE_PANO_ANIMATION_H_
