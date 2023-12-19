// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Step.h"
#include <array>
#include <iostream>

using WMS::Step;

constexpr size_t wash_size {12};

void run_wash(std::array<Step, wash_size>& wash)
{
  std::cout << "Accessing Steps via objects\n";
  for (auto& step : wash) {
    if (step.is_valid()) {
      step.run();
    }
  }
}

void run_wash(const std::array<Step*, wash_size>& wash)
{
  std::cout << "Accessing Steps via pointers\n";
  for (auto& step : wash) {
    if (step) {
      step->run();
    }
  }
}

int main()
{
  // Array of Step objects
  //
  std::array<Step, wash_size> colour_wash {
    Step {Step::Type::empty, 100},
    Step {Step::Type::fill, 100},
    Step {Step::Type::heat, 500},
    Step {Step::Type::wash, 1000},
    Step {Step::Type::rinse, 1500},
    Step {Step::Type::spin, 500},
    Step {Step::Type::dry, 100},
    Step {Step::Type::complete, 1000}
  };

  run_wash(colour_wash);

  // Stack based objects
  //
  Step empty {Step::Type::empty, 100};
  Step fill {Step::Type::fill, 100};
  Step heat {Step::Type::heat, 500};
  Step wash {Step::Type::wash, 1000};
  Step rinse {Step::Type::rinse, 1500};
  Step spin {Step::Type::spin, 500};
  Step dry {Step::Type::dry, 100};
  Step complete {Step::Type::complete, 1000};

  // Array of pointers to Step
  // objects partially initialised
  //
  std::array<Step*, wash_size> white_wash {
      &empty,
      &fill,
      &heat,
      &wash,
      &rinse,
      &spin,
      &dry,
      &complete
  };

  run_wash(white_wash);
}
