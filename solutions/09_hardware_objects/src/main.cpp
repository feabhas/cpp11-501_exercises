// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "GPIO.h"
#include "Peripherals.h"
#include "Timer.h"
#include <cstdint>

enum class SevenSegments { A = 8, B, C, D };

int main() {
  static Devices::GPIO gpiod{STM32F407::AHB1_Device::GPIO_D};

  gpiod.set_output(unsigned(SevenSegments::A));
  gpiod.set_output(unsigned(SevenSegments::B));
  gpiod.set_output(unsigned(SevenSegments::C));
  gpiod.set_output(unsigned(SevenSegments::D));

  for (unsigned i = 0; i < 10; ++i) {
    gpiod.clear(0xFu << unsigned(SevenSegments::A));
    gpiod.set(i << unsigned(SevenSegments::A));
    sleep(500);
  }

  gpiod.set(0xFu << unsigned(SevenSegments::A));
}
