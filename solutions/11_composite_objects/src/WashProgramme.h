// WashProgramme.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef WASHPROGRAMME_H
#define WASHPROGRAMME_H

#include "Step.h"
#include <array>

namespace Devices {
class SevenSegment;
}

namespace WMS {

class WashProgramme {
public:
  WashProgramme() = default;
  bool add(Step::Type step_type, uint32_t duration);
  void run();

private:
  friend void connect(WashProgramme &wash, Devices::SevenSegment &sseg);

  constexpr static unsigned wash_size{16};
  using Container = std::array<Step, wash_size>;

  Container steps{};
  Container::iterator next{std::begin(steps)};

  Devices::SevenSegment *display{};
};

} // namespace WMS

#endif // WASHPROGRAMME_H_
