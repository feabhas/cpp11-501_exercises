// MotorisedStep.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef MOTORISED_STEP_H
#define MOTORISED_STEP_H

#include "Step.h"

namespace Devices {
class Motor;
}

namespace WMS {

class MotorisedStep : public Step {
public:
  explicit MotorisedStep(Type step_type, uint32_t step_length,
                         Devices::Motor &motor);
  ~MotorisedStep() override;

  void run() override = 0;

protected:
  void activate_motor(uint32_t on_time, uint32_t off_time);

private:
  Devices::Motor *motor;
};

} // namespace WMS

#endif // MOTORISED_STEP_H_
