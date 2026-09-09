// Copyright 2026 Stuart Scott
#ifndef INCLUDE_PANO_LOG_H_
#define INCLUDE_PANO_LOG_H_

#include <iostream>
#include <string>

namespace Pano {
std::ostream& Error();
std::ostream& Info();
std::ostream& Debug();
};  // namespace Pano

#endif  // INCLUDE_PANO_LOG_H_
