// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include <memory>
#include<iostream>
#include <iomanip>
#include "GPIO.h"
#include "SevenSegment.h"
#include "Motor.h"
#include "SimpleStep.h"
#include "WashStep.h"
#include "SpinStep.h"
#include "RinseStep.h"
#include "WashProgramme.h"
#include "Console.h"

using WMS::Step;
using WMS::SimpleStep;
using WMS::WashStep;
using WMS::SpinStep;
using WMS::RinseStep;

namespace {
  std::unique_ptr<Devices::OutputDevice> make_7_segment(Devices::GPIO& port)
  {
    return std::make_unique<Devices::SevenSegment>(port);
  }

  [[maybe_unused]] std::unique_ptr<Devices::OutputDevice> make_console()
  {
    return std::make_unique<Devices::Console>();
  }
}


int main()
{
  Devices::GPIO gpiod {STM32F407::AHB1_Device::GPIO_D};
  Devices::Motor motor {gpiod};

  SimpleStep fill {Step::Type::fill, 1000};
  SimpleStep heat {Step::Type::heat, 2000};
  WashStep wash {Step::Type::wash, 2500, motor};
  RinseStep rinse {Step::Type::rinse, 2000, motor};
  SpinStep spin {Step::Type::spin, 3000, motor};
  SimpleStep dry {Step::Type::dry, 2400};
  SimpleStep complete {Step::Type::complete, 500};
  SimpleStep empty {Step::Type::empty, 500};

  WMS::WashProgramme white_wash {};

  white_wash.add(fill);
  white_wash.add(heat);
  white_wash.add(wash);
  white_wash.add(empty);
  white_wash.add(rinse);
  white_wash.add(spin);
  white_wash.add(dry);
  white_wash.add(complete);

  auto duration = white_wash.get_duration();
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "Expected wash time is :" << duration / 1000.0 << " seconds\n";

  auto sseg = make_7_segment(gpiod);
  connect (white_wash, *sseg.get());
  white_wash.run();

}
