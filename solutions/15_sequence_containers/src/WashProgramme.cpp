// WashProgramme.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "WashProgramme.h"
#include "SevenSegment.h"
#include <array>
#include <iomanip>
#include <iostream>

static constexpr unsigned init_size{12};

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

WashProgramme::WashProgramme() { steps.reserve(init_size); }

WashProgramme::WashProgramme(std::initializer_list<Step *> init_steps)
    : steps{init_steps} {}

void WashProgramme::add(Step &step) { steps.push_back(&step); }

void WashProgramme::run() {
  for (auto step : steps) {
    print_step_details(*step);
    if (display) {
      display->display(unsigned(step->get_type()));
    }
    step->run();
  }
}

void connect(WashProgramme &wash, Devices::OutputDevice &output) {
  wash.display = &output;
}

} // namespace WMS
