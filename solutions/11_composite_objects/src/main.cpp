// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "GPIO.h"
#include "SevenSegment.h"
#include "Step.h"
#include "WashProgramme.h"

using WMS::Step;

int main() {
  Devices::GPIO gpiod{STM32F407::AHB1_Device::GPIO_D};
  Devices::SevenSegment sseg{gpiod};

  WMS::WashProgramme white_wash{};

  white_wash.add(Step::Type::empty, 500);
  white_wash.add(Step::Type::fill, 1000);
  white_wash.add(Step::Type::heat, 2000);
  white_wash.add(Step::Type::wash, 2500);
  white_wash.add(Step::Type::rinse, 2000);
  white_wash.add(Step::Type::spin, 3000);
  white_wash.add(Step::Type::dry, 2400);
  white_wash.add(Step::Type::complete, 500);

  connect(white_wash, sseg);
  white_wash.run();
}
