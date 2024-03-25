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

void print_step_details(const WMS::Step &step) {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "Step '" << get_type_name(step) << "' "
            << "running for " << (step.get_duration() / 1000.0) << " seconds\n";
}
} // namespace

namespace WMS {

bool WashProgramme::add(Step &step) {
  // if the array is not full, only add valid steps
  if (next == std::end(steps) || !step.is_valid()) {
    return false;
  }
  *next = step;
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
// The run() method now uses the iterator 'next' to determine the end of the
// steps array (called the sential value). This means that the array can be
// partially filled and the programme will only run the steps that have been
// added. Also we don;t have to check if the step is valid as we know that the
// array is only partially filled with valid steps.
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
