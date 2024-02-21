// GPIO_C.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef GPIO_C_H
#define GPIO_C_H

#include <cstdint>

namespace Devices {

constexpr uintptr_t GPIOD_base { 0x4002'0C00u };

static volatile uint32_t *const GPIOD_moder = reinterpret_cast<uint32_t*>(GPIOD_base);
static volatile uint32_t *const GPIOD_odr = reinterpret_cast<uint32_t*>(GPIOD_base + 0x14u);
static volatile const uint32_t *const GPIOD_idr = reinterpret_cast<uint32_t*>(GPIOD_base + 0x10u);

void moder_set_as_output(volatile uint32_t* const reg, uint32_t bit);
void moder_set_as_input(volatile uint32_t* const reg, uint32_t bit);
void odr_set(volatile uint32_t* const reg, uint32_t pattern);
void odr_clear(volatile uint32_t* const reg, uint32_t pattern);
void odr_invert(volatile uint32_t* const reg, uint32_t pattern);
uint32_t idr_read(volatile uint32_t const* const reg);

} // namespace

#endif
