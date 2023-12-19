// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Peripherals.h"
#include "GPIO_C.h"
#include "Motor.h"
#include "SevenSegment.h"
#include "Timer.h"

int main()
{
  STM32F407::enable(STM32F407::AHB1_Device::GPIO_D);

  Devices::seven_segment_init();
  for (unsigned i = 0; i < 10; ++i) {
    Devices::seven_segment_display(i);
    sleep(500);
  }
  Devices::seven_segment_blank();

  Devices::motor_init();
  for (unsigned i = 0; i < 4; ++i) {
    Devices::motor_on();
    sleep(1000);

    Devices::motor_off();
    sleep(1000);
    Devices::motor_change_direction();
  }
}
