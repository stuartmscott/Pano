// Copyright 2026 Stuart Scott
#include <Pano/log.h>

#include <iostream>
#include <string>

namespace Pano {

std::ostream& Error() {
  std::cerr << "Error: ";
  return std::cerr;
}

std::ostream& Info() { return std::cout; }

constexpr bool DebugEnabled{false};
std::ostream NullStream(nullptr);

std::ostream& Debug() {
  if (DebugEnabled) {
    return std::cout;
  }
  return NullStream;
}
};  // namespace Pano
