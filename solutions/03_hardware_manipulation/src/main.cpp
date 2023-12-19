// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Peripherals.h" // STM32F407::enable
#include "Timer.h"       // sleep
#include <cstdint>

constexpr uint32_t GPIOD_base { 0x4002'0C00u };

static volatile uint32_t *const GPIOD_moder = reinterpret_cast<uint32_t*>(GPIOD_base);
static volatile uint32_t *const GPIOD_odr = reinterpret_cast<uint32_t*>(GPIOD_base + 0x14u);
static volatile const uint32_t *const GPIOD_idr = reinterpret_cast<uint32_t*>(GPIOD_base + 0x10u);

enum class LED { D6 = 8, D5, D4, D3 };
enum class SevenSegments { A = 8, B, C, D };
enum class Motor { on = 12, dir };

int main()
{
  STM32F407::enable(STM32F407::AHB1_Device::GPIO_D);

  // Enable Pin 8 for output
  // (1) C++11/14
  //   *GPIOD_moder &= ~(0x3u << static_cast<unsigned>(LED::D6) * 2);
  //   *GPIOD_moder |= (0x1u << static_cast<unsigned>(LED::D6) * 2);
  // (2) C++17 and C++ >= 23
  //   *GPIOD_moder &= ~(0b11u << unsigned(LED::D6) * 2); // C++17
  //   *GPIOD_moder |= (0b01u << unsigned(LED::D6) * 2);
  // (3) C++20 compilant code is also most efficient
  uint32_t moder = *GPIOD_moder;                   // read register
  moder &= ~(0b11u << unsigned(LED::D6) * 2);      // clear bits of interest
  moder |= (0b01u << unsigned(LED::D6) * 2);       // set bits
  *GPIOD_moder = moder;                            // write back to register

  // Toggle LED
  for (int i = 0; i < 5; ++i) {
    // Turn on
    auto outr = *GPIOD_odr;
    outr |= 0b1u << unsigned(LED::D6);
    *GPIOD_odr = outr;
    sleep(500);
    // Turn off
    *GPIOD_odr &= ~(0b1u << unsigned(LED::D6));       // C++20 warning
    sleep(500);
  }

  // Set motor control and direction as output
  moder = *GPIOD_moder;
  moder &= ~(0b11'11u << unsigned(Motor::on) * 2);
  moder |= (0b01'01u << unsigned(Motor::on) * 2);
  *GPIOD_moder = moder;

  // Drive motor
  for (int i = 0; i < 5; ++i) {
    // toggle direction and turn motor on
    auto outr = *GPIOD_odr;
    outr ^= (0b1u << unsigned(Motor::dir));
    outr |= (0b1u << unsigned(Motor::on));
    *GPIOD_odr = outr;
    sleep(500);
    // turn motor off
    *GPIOD_odr &= ~(0b1u << unsigned(Motor::on));     // C++20 warning
    sleep(500);
  }

  // Set Seven Segment output bits in Mode Register
  // (1)  Terse example
  moder = *GPIOD_moder;
  moder &= ~(0xFFu << unsigned(SevenSegments::A) * 2); // clear PD.8..PD.11 modes
  moder |= (0x55u << unsigned(SevenSegments::A) * 2);  // set PD.8..PD.11 as output
  *GPIOD_moder = moder;

  // (2) Explicit example
  // This will generate exactly the same assembler as (1)
  moder = *GPIOD_moder;
  moder &= ~(0b11u << unsigned(SevenSegments::A) * 2); // clear PD.8 modes
  moder |= (0b01u << unsigned(SevenSegments::A) * 2);  // set PD.8 as output
  moder &= ~(0b11u << unsigned(SevenSegments::B) * 2); // clear PD.9 modes
  moder |= (0b01u << unsigned(SevenSegments::B) * 2);  // set PD.9 as output
  moder &= ~(0b11u << unsigned(SevenSegments::C) * 2); // clear PD.10 modes
  moder |= (0b01u << unsigned(SevenSegments::C) * 2);  // set PD.10 as output
  moder &= ~(0b11u << unsigned(SevenSegments::D) * 2); // clear PD.11 modes
  moder |= (0b01u << unsigned(SevenSegments::D) * 2);  // set PD.11 as output
  *GPIOD_moder = moder;

  // Display 0..9 on Seven Segment
  for (unsigned i = 0; i < 10; ++i) {
    auto outr = *GPIOD_odr;
    outr &= ~(0b11'11u << unsigned(SevenSegments::A)); // clear bits
    outr |= (i << unsigned(SevenSegments::A));
    *GPIOD_odr = outr;
    sleep(500);
  }
}
