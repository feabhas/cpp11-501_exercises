// Step.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef STEP_H
#define STEP_H

#include <cstdint>

namespace WMS {

class Step {
public:
  enum class Type { empty = 1, fill, heat, wash, rinse, spin, dry, complete };

  Step() = delete; // refactored to remove invalid steps
  explicit Step(Type step_type, uint32_t step_length);
  virtual ~Step() = default;

  virtual void run() = 0;

  Type get_type() const { return type; }
  uint32_t get_duration() const { return duration; }

private:
  Type type;
  uint32_t duration;
};

} // namespace WMS

#endif // STEP_H_
