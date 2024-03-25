// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "GPIO.h"
#include "Motor.h"
#include "SevenSegment.h"
#include "Step.h"
#include "Timer.h"
#include <array>
#include <cstdint>
#include <iostream>

using WMS::Step;

int main() {
  Devices::GPIO gpiod{STM32F407::AHB1_Device::GPIO_D};

  Devices::SevenSegment sseg{gpiod};
  for (unsigned i = 0; i < 10; ++i) {
    sseg.display(i);
    sleep(1000);
  }
  sseg.blank();

  Devices::Motor motor{gpiod};
  for (unsigned i = 0; i < 5; ++i) {
    motor.on();
    sleep(1000);
    motor.off();
    sleep(500);
    motor.change_direction();
  }
}
