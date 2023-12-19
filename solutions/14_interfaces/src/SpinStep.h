// SpinStep.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef SPINSTEP_H
#define SPINSTEP_H

#include "MotorisedStep.h"

namespace Devices {
  class Motor;
}

namespace WMS {

class SpinStep : public MotorisedStep {
public:
  ~SpinStep() override = default;
  explicit SpinStep(Type step_type, uint32_t step_length, Devices::Motor& motor)
  : MotorisedStep {step_type, step_length, motor}
  {}

  void run() override
  {
    activate_motor(750, 250);
  }
};

} // namespace

#endif // WASHSTEP_H_
