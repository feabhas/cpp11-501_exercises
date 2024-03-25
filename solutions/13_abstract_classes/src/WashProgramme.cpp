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

bool WashProgramme::add(Step &step) {
  // If the array is not full and the step is valid, add it to the array
  if (next == std::end(steps) || !step.is_valid()) {
    return false;
  }
  *next = &step;
  ++next;
  return true;
}

#if 1
void WashProgramme::run() {
  for (auto step : steps) { // could be auto* step - very much a matter of style
    if (step) {             // Check for nullptr array members
      print_step_details(*step);
      if (display) {
        display->display(unsigned(step->get_type()));
      }
      step->run();
    }
  }
}
#else
// Alternative implementation using iterators
// This does not need to check for nullptrs
void WashProgramme::run() {
  for (auto step = std::begin(steps); step != next; ++step) {
    Step &current_step = **step;
    print_step_details(current_step);
    if (display) {
      display->display(unsigned(current_step.get_type()));
    }
    current_step.run();
  }
}

#endif

void connect(WashProgramme &wash, Devices::SevenSegment &sseg) {
  wash.display = &sseg;
}

} // namespace WMS
