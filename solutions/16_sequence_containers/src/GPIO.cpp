// GPIO.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "GPIO.h"
#include "Memory_map.h"

namespace Devices {

struct Registers {
  uint32_t mode;
  uint32_t output_type;
  uint32_t output_speed;
  uint32_t pull_up_down;
  uint32_t input;
  uint32_t output;
  // not used
  // uint32_t bit_set_reset;
  // uint32_t lock;
  // uint32_t alt_fn_low;
  // uint32_t alt_fn_high;
};

static_assert(sizeof(Registers) == 24);

GPIO::GPIO(STM32F407::AHB1_Device device)
    : port{reinterpret_cast<Registers *>(device_base_address(device))} {
  STM32F407::enable(device);
}

void GPIO::set_input(unsigned pin) {
  auto moder = port->mode;
  moder &= ~(0b11u << pin * 2);
  port->mode = moder;
}

void GPIO::set_output(unsigned pin) {
  auto moder = port->mode;
  moder &= ~(0b11u << pin * 2);
  moder |= (0b01u << pin * 2);
  port->mode = moder;
}

void GPIO::set(uint32_t pattern) {
  uint32_t value = port->output;
  value |= pattern;
  port->output = value;
}

void GPIO::clear(uint32_t pattern) {
  uint32_t value = port->output;
  value &= ~pattern;
  port->output = value;
}

uint32_t GPIO::mode() const { return port->mode; }

uint32_t GPIO::read() const { return port->input; }

} // namespace Devices
