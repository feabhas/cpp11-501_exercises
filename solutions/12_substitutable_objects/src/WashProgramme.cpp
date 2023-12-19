// WashProgramme.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <iostream>
#include <iomanip>
#include <iostream>
#include "WashProgramme.h"
#include "SevenSegment.h"

namespace {
  using WMS::Step;
  const char* get_type_name(const Step& step)
  {
    using Type = Step::Type;
    switch (step.get_type()) {
      case Step::Type::invalid: return "invalid";
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
}

namespace WMS {

bool WashProgramme::add(Step& step)
{
  if (next == std::end(steps)) {
    return false;
  }
  *next = &step;
  ++next;
  return true;
}

void WashProgramme::run()
{
  for (auto step : steps) {
    if (step) {
      std::cout << std::fixed << std::setprecision(2);
      std::cout << "Step '" << get_type_name(*step) << "' "
                << "running for " << (step->get_duration() / 1000.0) << " seconds\n";
      if (display) {
        display->display(unsigned(step->get_type()));
      }
      step->run();
    }
  }
}

void connect(WashProgramme& wash, Devices::SevenSegment& output)
{
  wash.display = &output;
}


} // namespace
