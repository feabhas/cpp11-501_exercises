// SevenSegment.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "SevenSegment.h"
#include "GPIO_C.h"

namespace Devices {

enum class SevenSegments { A = 8, B, C, D };

void seven_segment_init()
{
  moder_set_as_output(GPIOD_moder, unsigned(SevenSegments::A));
  moder_set_as_output(GPIOD_moder, unsigned(SevenSegments::B));
  moder_set_as_output(GPIOD_moder, unsigned(SevenSegments::C));
  moder_set_as_output(GPIOD_moder, unsigned(SevenSegments::D));
  seven_segment_blank();
}

void seven_segment_display(unsigned val)
{
  val &= 0xF;
  odr_clear(GPIOD_odr, 0xFu << unsigned(SevenSegments::A));
  odr_set(GPIOD_odr, val << unsigned(SevenSegments::A));
}

void seven_segment_blank()
{
  seven_segment_display(0xF);
}

} // namespace
