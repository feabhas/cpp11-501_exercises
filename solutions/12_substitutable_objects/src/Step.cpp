// Step.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Step.h"
#include "SevenSegment.h"
#include "Timer.h"

namespace WMS {

Step::Step(Type step_type, uint32_t step_length)
    : type{step_type}, duration{step_length} {}

void Step::run() { sleep(duration); }

} // namespace WMS
