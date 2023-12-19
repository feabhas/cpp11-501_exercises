// MotorisedStep.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Timer.h"
#include "MotorisedStep.h"
#include "Motor.h"

namespace WMS {

MotorisedStep::MotorisedStep(Type step_type, uint32_t step_length,
                          Devices::Motor& motor)
: Step {step_type, step_length}, motor {motor}
{ }

MotorisedStep::~MotorisedStep()
{
    motor.off();
}

void MotorisedStep::activate_motor(uint32_t on_time, uint32_t off_time)
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
