// Step.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Step.h"
#include "SevenSegment.h"
#include "Timer.h"
#include <iomanip>
#include <iostream>

namespace WMS {

Step::Step()
{
  std::cout << "Step()" << '\n';
}

Step::Step(Type step_type, uint32_t step_length)
: type {step_type}, duration {step_length}
{
  std::cout << "Step(" << int(type) << ", " << duration << ')' << '\n';
}

Step::  ~Step()
{
  std::cout << "~Step(" << int(type) << ")" << '\n';
}

void Step::run()
{
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "Step '" << get_type_name() << "' "
            << "running for " << (duration / 1000.0) << " seconds\n";
  sleep(duration);
}

const char* Step::get_type_name() const
{
  switch (type) {
    case Type::invalid: return "invalid";
    case Type::empty: return "empty";
    case Type::fill: return "fill";
    case Type::heat: return "heat";
    case Type::wash: return "wash";
    case Type::rinse: return "rinse";
    case Type::spin: return "spin";
    case Type::dry: return "dry";
    case Type::complete: return "complete";
  }
  return "UNKNOWN";
};

} // namespace
