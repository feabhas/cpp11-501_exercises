// WashProgramme.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "WashProgramme.h"
#include "SevenSegment.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

static constexpr unsigned init_size{12};

namespace {
constexpr std::array string_map[] = {"invalid", "empty", "fill",
                                     "heat",    "wash",  "rinse",
                                     "spin",    "dry",   "complete"};

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

#if 1
uint32_t WashProgramme::get_duration() const {
  unsigned total{};
  std::for_each(std::begin(steps), std::end(steps),
                [&total](auto const &step) { total += step->get_duration(); });
  return total;
}
#else
// Alternative version using std::accumulate
uint32_t WashProgramme::get_duration() const {
  auto total = std::accumulate(steps.begin(), steps.end(), 0U,
                               [](auto total, auto const &step) {
                                 return total + step->get_duration();
                               });
  return total;
}
#endif

} // namespace WMS
