// WashProgramme.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef WASHPROGRAMME_H
#define WASHPROGRAMME_H

#include <vector>
#include "Step.h"
#include "OutputDevice.h"

namespace Devices {
class OutputDevice;
}

namespace WMS {

class WashProgramme {
public:
  WashProgramme();
  WashProgramme(std::initializer_list<Step*> init_steps);

  bool add(Step& step);
  void run();

  uint32_t get_duration() const;

private:
  friend void connect(WashProgramme& wash, Devices::OutputDevice& output);

  using Container = std::vector<Step*>;
  Container steps {};
  Devices::OutputDevice* display;
};

} // namespace Application

#endif // WASHPROGRAMME_H_
