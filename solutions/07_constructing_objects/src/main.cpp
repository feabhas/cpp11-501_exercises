// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Step.h"
#include <cassert>

using WMS::Step;

int main() {
  Step empty{Step::Type::empty, 100};
  Step fill{Step::Type::fill, 100};
  Step heat{Step::Type::heat, 500};
  Step wash{Step::Type::wash, 1000};
  Step rinse{Step::Type::rinse, 1500};
  Step spin{Step::Type::spin, 500};
  Step dry{Step::Type::dry, 100};
  Step complete{Step::Type::complete, 1000};

  empty.run();
  fill.run();
  heat.run();
  wash.run();
  rinse.run();
  spin.run();
  dry.run();
  complete.run();

  Step blank{};
  assert(!blank.is_valid());
  assert(wash.is_valid());
}
