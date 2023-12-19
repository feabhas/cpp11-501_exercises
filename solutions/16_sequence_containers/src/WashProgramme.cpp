// WashProgramme.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <iostream>
#include <iomanip>
#include <iostream>
#include "WashProgramme.h"
#include "SevenSegment.h"

static constexpr unsigned init_size {12};

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

WashProgramme::WashProgramme()
{
  steps.reserve(init_size);
}

WashProgramme::WashProgramme(std::initializer_list<Step*> init_steps)
: steps {init_steps}
{ }

bool WashProgramme::add(Step& step)
{
  steps.push_back(&step);
  return true;
}

void WashProgramme::run()
{
  for (auto step : steps) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Step '" << get_type_name(*step) << "' "
              << "running for " << (step->get_duration() / 1000.0) << " seconds\n";
    if (display) {
      display->display(unsigned(step->get_type()));
    }
    step->run();
  }
}

void connect(WashProgramme& wash, Devices::OutputDevice& output)
{
  wash.display = &output;
}


} // namespace Application
