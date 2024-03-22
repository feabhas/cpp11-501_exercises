// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Step.h"
#include <array>
#include <iostream>

using WMS::Step;

#if 1

// Fixed sized Array based model
// This requires the size of the array to be known at compile time
// This is the simplest model and is the generally efficient
// However, it reuires:
// (1) The known upper bound of the array size
// (2) The run_wash must deal with 'invalid' steps

constexpr size_t wash_size{16};
using wash_t = std::array<Step, wash_size>;

void run_wash(wash_t &wash) {
  std::cout << "Accessing Steps via objects\n";
  for (auto &step : wash) {
    if (step.is_valid()) {
      step.run();
    }
  }
}

int main() {
  // Array of Step objects
  // Colour Wash
  wash_t colour_wash{
      Step{Step::Type::fill, 100},  Step{Step::Type::heat, 500},
      Step{Step::Type::wash, 1000}, Step{Step::Type::empty, 100},
      Step{Step::Type::fill, 100},  Step{Step::Type::rinse, 1500},
      Step{Step::Type::empty, 100}, Step{Step::Type::spin, 500},
      Step{Step::Type::dry, 100},   Step{Step::Type::complete, 1000}};

  run_wash(colour_wash);

  // White Wash (includes prewash)
  wash_t white_wash{
      Step{Step::Type::fill, 100},     Step{Step::Type::wash, 1000},
      Step{Step::Type::empty, 100},    Step{Step::Type::fill, 100},
      Step{Step::Type::heat, 500},     Step{Step::Type::wash, 1000},
      Step{Step::Type::empty, 100},    Step{Step::Type::fill, 100},
      Step{Step::Type::rinse, 1500},   Step{Step::Type::empty, 100},
      Step{Step::Type::spin, 500},     Step{Step::Type::dry, 100},
      Step{Step::Type::complete, 1000}};
  run_wash(white_wash);
}

#else

// Iterator based model
// This model is more flexible as it can handle any size of array
// However, it requires the run_wash function to be passed the begin and end
// iterators

void run_wash(Step *const begin, Step *const end) {
  std::cout << "Accessing Steps via iterators\n";
  for (auto it = begin; it != end; ++it) {
    it->run();
  }
}

int main() {
  // Array of Step objects
  // Colour Wash
  // std::array<Step, 10>
  std::array colour_wash{
      Step{Step::Type::fill, 100},  Step{Step::Type::heat, 500},
      Step{Step::Type::wash, 1000}, Step{Step::Type::empty, 100},
      Step{Step::Type::fill, 100},  Step{Step::Type::rinse, 1500},
      Step{Step::Type::empty, 100}, Step{Step::Type::spin, 500},
      Step{Step::Type::dry, 100},   Step{Step::Type::complete, 1000}};

  run_wash(std::begin(colour_wash), std::end(colour_wash));

  // White Wash (includes prewash)
  // std::array<Step, 13>
  std::array white_wash{
      Step{Step::Type::fill, 100},     Step{Step::Type::wash, 1000},
      Step{Step::Type::empty, 100},    Step{Step::Type::fill, 100},
      Step{Step::Type::heat, 500},     Step{Step::Type::wash, 1000},
      Step{Step::Type::empty, 100},    Step{Step::Type::fill, 100},
      Step{Step::Type::rinse, 1500},   Step{Step::Type::empty, 100},
      Step{Step::Type::spin, 500},     Step{Step::Type::dry, 100},
      Step{Step::Type::complete, 1000}};

  run_wash(std::begin(white_wash), std::end(white_wash));
}

#endif
