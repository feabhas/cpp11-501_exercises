// WashProgramme.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef WASHPROGRAMME_H
#define WASHPROGRAMME_H

#include "Step.h"
#include <array>

namespace Devices {
class OutputDevice;
}

namespace WMS {

class WashProgramme {
public:
  WashProgramme() = default;
  bool add(Step &step);
  void run();

private:
  friend void connect(WashProgramme &wash, Devices::OutputDevice &output);

  constexpr static unsigned wash_size{16};
  using Container = std::array<Step *, wash_size>;

  Container steps{};
  Container::iterator next{std::begin(steps)};

  Devices::OutputDevice *display{};
};

} // namespace WMS

#endif // WASHPROGRAMME_H_
