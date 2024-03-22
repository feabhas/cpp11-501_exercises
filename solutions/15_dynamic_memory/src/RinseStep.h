// RinseStep.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef RINSESTEP_H
#define RINSESTEP_H

#include "MotorisedStep.h"

namespace Devices {
class Motor;
}

namespace WMS {

class RinseStep : public MotorisedStep {
public:
  ~RinseStep() override = default;
  explicit RinseStep(Type step_type, uint32_t step_length,
                     Devices::Motor &motor)
      : MotorisedStep{step_type, step_length, motor} {}

  void run() override { activate_motor(500, 500); }
};

} // namespace WMS

#endif // WASHSTEP_H_
