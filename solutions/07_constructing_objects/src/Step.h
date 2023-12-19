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
  enum class Type {
    invalid, empty, fill, heat,
    wash, rinse, spin, dry, complete
  };

  Step();
  explicit Step(Type step_type, uint32_t step_length);
  ~Step();

  void run();

  bool is_valid() const { return type != Type::invalid; }

private:
  const char* get_type_name() const;

  Type type {};
  uint32_t duration {};
};

} // namespace

#endif // STEP_H_
