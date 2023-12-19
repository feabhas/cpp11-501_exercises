// Motor.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Motor.h"
#include "GPIO_C.h"

namespace Devices {

enum class Motor { on = 12, dir };

void motor_init()
{
  moder_set_as_output(GPIOD_moder, unsigned(Motor::on));
  moder_set_as_output(GPIOD_moder, unsigned(Motor::dir));
  motor_off();
}

void motor_on()
{
  odr_set(GPIOD_odr, 0b1 << unsigned(Motor::on));
}

void motor_off()
{
  odr_clear(GPIOD_odr, 0b1 << unsigned(Motor::on));
}

void motor_change_direction()
{
  odr_invert(GPIOD_odr, 0b1 << unsigned(Motor::dir));
}

} // namespace
