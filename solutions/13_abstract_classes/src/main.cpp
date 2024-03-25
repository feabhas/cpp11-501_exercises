// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "GPIO.h"
#include "Motor.h"
#include "RinseStep.h"
#include "SevenSegment.h"
#include "SimpleStep.h"
#include "SpinStep.h"
#include "WashProgramme.h"
#include "WashStep.h"

using WMS::RinseStep;
using WMS::SimpleStep;
using WMS::SpinStep;
using WMS::Step;
using WMS::WashStep;

int main() {
  Devices::GPIO gpiod{STM32F407::AHB1_Device::GPIO_D};
  Devices::SevenSegment sseg{gpiod};
  Devices::Motor motor{gpiod};

  SimpleStep fill{Step::Type::fill, 1000};
  SimpleStep heat{Step::Type::heat, 2000};
  WashStep wash{Step::Type::wash, 2500, motor};
  RinseStep rinse{Step::Type::rinse, 2000, motor};
  SpinStep spin{Step::Type::spin, 3000, motor};
  SimpleStep dry{Step::Type::dry, 2400};
  SimpleStep complete{Step::Type::complete, 500};
  SimpleStep empty{Step::Type::empty, 500};

  WMS::WashProgramme white_wash{};

  white_wash.add(fill);
  white_wash.add(heat);
  white_wash.add(wash);
  white_wash.add(empty);
  white_wash.add(rinse);
  white_wash.add(spin);
  white_wash.add(dry);
  white_wash.add(complete);

  connect(white_wash, sseg);
  white_wash.run();
}
