// SimpleStep.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Timer.h"
#include "SimpleStep.h"

namespace WMS {

SimpleStep::SimpleStep(Type step_type, uint32_t step_length)
: Step(step_type, step_length)
{}

void SimpleStep::run()
{
  sleep(get_duration());
}

} // namespace
