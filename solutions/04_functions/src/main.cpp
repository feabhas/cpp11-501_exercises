// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Peripherals.h"
#include "Timer.h"
#include <array>
#include <cstdint>

constexpr uintptr_t GPIOD_base { 0x4002'0C00u };

static volatile uint32_t *const GPIOD_moder = reinterpret_cast<uint32_t*>(GPIOD_base);
static volatile uint32_t *const GPIOD_odr = reinterpret_cast<uint32_t*>(GPIOD_base + 0x14u);
static volatile const uint32_t *const GPIOD_idr = reinterpret_cast<uint32_t*>(GPIOD_base + 0x10u);

inline void moder_set_as_output(volatile uint32_t* const reg,
                                uint32_t bit)
{
  auto moder = *reg;
  moder &= ~(0b11u << (bit * 2)); // clear mode
  moder |= (0b01u << (bit * 2));  // set as output
  *reg = moder;
}

inline void moder_set_as_input(volatile uint32_t* const reg,
                               uint32_t bit)
{
  auto moder = *reg;
  moder &= ~(0b11u << (bit * 2)); // ste as input
  *reg = moder;
}

inline void odr_set(volatile uint32_t* const reg, uint32_t pattern)
{
  auto value = *reg;
  value |= pattern;
  *reg = value;
}

inline void odr_clear(volatile uint32_t* const reg,
                      uint32_t pattern)
{
  auto value = *reg;
  value &= ~pattern;
  *reg = value;
}

inline void odr_invert(volatile uint32_t* const reg,
                       uint32_t pattern)
{
  auto value = *reg;
  value ^= pattern;
  *reg = value;
}

inline uint32_t idr_read(volatile uint32_t const* const reg)
{
  return *reg;
}

// -----------------------------------------------------------------------------
// Seven-segment functions
//
void seven_segment_init();
void seven_segment_display(unsigned val);
void seven_segment_blank();

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

// -----------------------------------------------------------------------------
// Motor functions
//
void motor_init();
void motor_on();
void motor_off();
void motor_change_direction();

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

// -----------------------------------------------------------------------------
// Main application
//

int main()
{
  STM32F407::enable(STM32F407::AHB1_Device::GPIO_D);

  seven_segment_init();

  for (unsigned i = 0; i < 10; ++i) {
    seven_segment_display(i);
    sleep(500);
  }
  seven_segment_blank();

  motor_init();

  for (unsigned i = 0; i < 4; ++i) {
    motor_on();
    sleep(1000);
    motor_off();
    sleep(1000);
    motor_change_direction();
  }
}
