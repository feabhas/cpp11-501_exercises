// WashProgramme.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef WASHPROGRAMME_H
#define WASHPROGRAMME_H

#include "OutputDevice.h"
#include "Step.h"
#include <vector>

namespace Devices {
class OutputDevice;
}

namespace WMS {

class WashProgramme {
public:
  WashProgramme();
  WashProgramme(std::initializer_list<Step *> init_steps);

  void add(Step &step);
  void run();

private:
  friend void connect(WashProgramme &wash, Devices::OutputDevice &output);

  using Container = std::vector<Step *>;
  Container steps{};
  Devices::OutputDevice *display{};
};

} // namespace WMS

#endif // WASHPROGRAMME_H_
