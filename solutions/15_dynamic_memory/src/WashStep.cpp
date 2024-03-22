// WashStep.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "WashStep.h"
#include "Motor.h"

namespace WMS {

static constexpr uint32_t on_time{250};
static constexpr uint32_t off_time{250};

WashStep::WashStep(Type step_type, uint32_t step_length, Devices::Motor &motor)
    : MotorisedStep{step_type, step_length, motor} {}

void WashStep::run() { activate_motor(on_time, off_time); }

} // namespace WMS
