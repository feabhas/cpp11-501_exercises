// SevenSegment.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "SevenSegment.h"
#include "GPIO.h"

namespace Devices {

enum class Pins { A = 8, B, C, D };

constexpr auto mask{0b11'11u << unsigned(Pins::A)};

SevenSegment::SevenSegment(GPIO &gpio) : port{&gpio} {
  gpio.set_output(unsigned(Pins::A));
  gpio.set_output(unsigned(Pins::B));
  gpio.set_output(unsigned(Pins::C));
  gpio.set_output(unsigned(Pins::D));
  blank();
}

SevenSegment::~SevenSegment() { blank(); }

void SevenSegment::blank() { port->set(mask); }

void SevenSegment::display(unsigned value) {
  port->clear(mask);
  port->set((value << unsigned(Pins::A)) & mask);
}

} // namespace Devices
