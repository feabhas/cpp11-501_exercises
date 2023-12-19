// SevenSegment.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "SevenSegment.h"
#include "GPIO.h"

namespace Devices {

enum class Pins { A = 8, B, C, D };

SevenSegment::SevenSegment(GPIO& gpio)
: port {&gpio}
{
  gpio.set_output(unsigned(Pins::A));
  gpio.set_output(unsigned(Pins::B));
  gpio.set_output(unsigned(Pins::C));
  gpio.set_output(unsigned(Pins::D));
  blank();
}

SevenSegment::~SevenSegment()
{
  blank();
}

void SevenSegment::blank()
{
  port->set(0b11'11u << unsigned(Pins::A));
}

void SevenSegment::display(unsigned value)
{
  port->clear(0b11'11u << unsigned(Pins::A));
  port->set((value&0xFu) << unsigned(Pins::A));
}


} // namespace
