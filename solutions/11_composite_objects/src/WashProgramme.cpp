// WashProgramme.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "WashProgramme.h"
#include "SevenSegment.h"
#include <array>
#include <iomanip>
#include <iostream>

namespace {

constexpr std::array string_map{"invalid", "empty", "fill", "heat",    "wash",
                                "rinse",   "spin",  "dry",  "complete"};

const char *get_type_name(const WMS::Step &step) {
  return string_map[unsigned(step.get_type())];
};

void print_step_details(WMS::Step &step) {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "Step '" << get_type_name(step) << "' "
            << "running for " << (step.get_duration() / 1000.0) << " seconds\n";
}

} // namespace

namespace WMS {

bool WashProgramme::add(Step::Type step_type, uint32_t duration) {
  if (next == std::end(steps) || step_type == Step::Type::invalid) {
    return false;
  }
  *next = Step{step_type, duration};
  ++next;
  return true;
}

#if 1
void WashProgramme::run() {
  for (auto &step : steps) {
    if (step.is_valid()) {
      print_step_details(step);
      if (display) {
        display->display(unsigned(step.get_type()));
      }
      step.run();
    }
  }
}
#else
// The run() method has been refactored to use the iterator next to determine
// the end of the steps array (the sential value). This is a more idiomatic way
// to iterate over a container in C++.
void WashProgramme::run() {
  for (auto step = std::begin(steps); step != next; ++step) {
    print_step_details(*step);
    if (display) {
      display->display(unsigned(step->get_type()));
    }
    step->run();
  }
}

#endif

void connect(WashProgramme &wash, Devices::SevenSegment &sseg) {
  wash.display = &sseg;
}

} // namespace WMS
