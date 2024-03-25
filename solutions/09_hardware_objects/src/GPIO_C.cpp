// GPIO_C.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "GPIO_C.h"
#include <cassert>

namespace Devices {

void moder_set_as_output(volatile uint32_t *const reg, uint32_t bit) {
  assert(bit < 16u); // 16 bits per register (2 bits per pin
  auto moder = *reg;
  moder &= ~(0b11u << (bit * 2)); // clear mode
  moder |= (0b01u << (bit * 2));  // set as output
  *reg = moder;
}

void moder_set_as_input(volatile uint32_t *const reg, uint32_t bit) {
  assert(bit < 16u); // 16 bits per register (2 bits per pin
  auto moder = *reg;
  moder &= ~(0b11u << (bit * 2)); // ste as input
  *reg = moder;
}

void odr_set(volatile uint32_t *const reg, uint32_t pattern) {
  auto value = *reg;
  value |= (pattern & 0xFFFFu);
  *reg = value;
}

void odr_clear(volatile uint32_t *const reg, uint32_t pattern) {
  auto value = *reg;
  value &= ~(pattern & 0xFFFFu);
  *reg = value;
}

void odr_invert(volatile uint32_t *const reg, uint32_t pattern) {
  auto value = *reg;
  value ^= (pattern & 0xFFFFu);
  *reg = value;
}

uint32_t idr_read(volatile uint32_t const *const reg) { return *reg; }

} // namespace Devices
