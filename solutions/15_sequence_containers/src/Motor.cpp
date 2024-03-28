// Motor.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Motor.h"
#include "GPIO.h"

namespace Devices {

enum class Pins { on = 12, dir };

Motor::Motor(GPIO &gpio) : port{&gpio} {
  gpio.set_output(unsigned(Pins::on));
  gpio.set_output(unsigned(Pins::dir));
  off();
}

Motor::~Motor() { off(); }

void Motor::on() { port->set(0x1u << unsigned(Pins::on)); }

void Motor::off() { port->clear(0x1u << unsigned(Pins::on)); }

void Motor::change_direction() {
  constexpr unsigned mask{0x1u << unsigned(Pins::dir)};
  if ((port->read() & mask) != 0) {
    port->clear(mask);
  } else {
    port->set(mask);
  }
}

} // namespace Devices
