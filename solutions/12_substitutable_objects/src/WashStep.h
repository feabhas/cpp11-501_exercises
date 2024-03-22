// WashStep.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef WASHSTEP_H
#define WASHSTEP_H

#include "Step.h"

namespace Devices {
class Motor;
}

namespace WMS {

class WashStep : public Step {
public:
  ~WashStep() override;
  explicit WashStep(Type step_type, uint32_t step_length,
                    Devices::Motor &motor);
  void run() override;

private:
  Devices::Motor &motor;
};

} // namespace WMS

#endif // WASHSTEP_H_
