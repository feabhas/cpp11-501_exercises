// main.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Peripherals.h" // STM32F407::enable
#include "Timer.h"       // sleep
#include <array>
#include <cstdint>

constexpr uint32_t GPIOD_base { 0x4002'0C00u };

static volatile uint32_t *const GPIOD_moder = reinterpret_cast<uint32_t*>(GPIOD_base);
static volatile uint32_t *const GPIOD_odr = reinterpret_cast<uint32_t*>(GPIOD_base + 0x14u);
static volatile const uint32_t *const GPIOD_idr = reinterpret_cast<uint32_t*>(GPIOD_base + 0x10u);

enum class LED { D6 = 8, D5, D4, D3 };
enum class SevenSegments { A = 8, B, C, D };
enum class Motor { on = 12, dir };

enum class Steps : uint8_t {
  invalid, empty, fill, heat,
  wash, rinse, spin, dry, complete
};

constexpr size_t colour_wash_size {12};

#if 1 // part 1

// Array of Step objects
std::array<Steps, colour_wash_size> colour_wash {
    Steps::fill,
    Steps::heat,
    Steps::wash,
    Steps::empty,
    Steps::fill,
    Steps::rinse,
    Steps::empty,
    Steps::spin,
    Steps::dry,
    Steps::complete,
};

int main()
{
  STM32F407::enable(STM32F407::AHB1_Device::GPIO_D);

  auto moder = *GPIOD_moder;
  moder &= ~(0xFFu << unsigned(SevenSegments::A) * 2);
  moder |= (0x55u << unsigned(SevenSegments::A) * 2);
  *GPIOD_moder = moder;

  // use range-for loop
  for (auto type : colour_wash) {
    if (type != Steps::invalid) {
      auto outr = *GPIOD_odr;
      outr &= ~(0b11'11u << unsigned(SevenSegments::A));
      outr |= (unsigned(type) << unsigned(SevenSegments::A));
      *GPIOD_odr = outr;
      sleep(1000);
    }
  }
}

#else // Optional part

struct Step {
  Steps type;
  duration_mSec delay;
};

// Array of Step objects
std::array<Step, colour_wash_size> colour_wash {
    Step {Steps::fill, 500}, Step {Steps::heat, 500}, Step {Steps::wash, 1000},
    Step {Steps::empty, 500}, Step {Steps::fill, 500}, Step {Steps::rinse, 1000},
    Step {Steps::empty, 500}, Step {Steps::spin, 1000}, Step {Steps::dry, 500},
    Step {Steps::complete, 1000}
};

int main()
{
  STM32F407::enable(STM32F407::AHB1_Device::GPIO_D);

  auto moder = *GPIOD_moder;
  moder &= ~(0xFFu << unsigned(SevenSegments::A) * 2);
  moder |= (0x55u << unsigned(SevenSegments::A) * 2);
  *GPIOD_moder = moder;

  for (auto step : colour_wash) {
    if (step.type != Steps::invalid) {
      auto outr = *GPIOD_odr;
      outr &= ~(0b11'11u << unsigned(SevenSegments::A));
      outr |= (unsigned(step.type) << unsigned(SevenSegments::A));
      *GPIOD_odr = outr;
      sleep(step.delay);
    }
  }
}

#endif
