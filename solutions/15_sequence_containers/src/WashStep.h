// WashStep.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef WASHSTEP_H
#define WASHSTEP_H

#include "MotorisedStep.h"

namespace Devices {
class Motor;
}

namespace WMS {

class WashStep : public MotorisedStep {
public:
  explicit WashStep(Type step_type, uint32_t step_length,
                    Devices::Motor &motor);
  ~WashStep() override = default;
  void run() override;
};

} // namespace WMS

#endif // WASHSTEP_H_
