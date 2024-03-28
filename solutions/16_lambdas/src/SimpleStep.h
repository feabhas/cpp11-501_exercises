// SimpleStep.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef SIMPLESTEP_H
#define SIMPLESTEP_H

#include "Step.h"
#include <cstdint>

namespace WMS {

class SimpleStep : public Step {
public:
  SimpleStep() = default;
  explicit SimpleStep(Type step_type, uint32_t step_length);

  void run() override;
};

} // namespace WMS

#endif // SIMPLESTEP_H_
