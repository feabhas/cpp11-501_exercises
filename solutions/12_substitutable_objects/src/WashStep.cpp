// WashStep.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "WashStep.h"
#include "Motor.h"
#include "Timer.h"
#include <cassert>

namespace WMS {

static constexpr uint32_t on_time {250};
static constexpr uint32_t off_time {250};

WashStep::~WashStep()
{
  motor.off();
}

WashStep::WashStep(Type step_type, uint32_t step_length, Devices::Motor& motor)
: Step {step_type, step_length}, motor {motor}
{}

void WashStep::run()
{
  auto const num_changes = Step::get_duration() / (on_time + off_time);

  for (unsigned i {}; i < num_changes; ++i) {
    motor.on();
    sleep(on_time);
    motor.change_direction();
    sleep(off_time);
  }
  motor.off();
}

} // namespace
