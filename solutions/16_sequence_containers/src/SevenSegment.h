// SevenSegment.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef SEVENSEGMENT_H
#define SEVENSEGMENT_H

#include "OutputDevice.h"

namespace Devices {
class GPIO;

class SevenSegment : public OutputDevice {
public:
  SevenSegment(GPIO &gpio);
  ~SevenSegment();

protected:
  void display(unsigned int value) override;
  void blank();

private:
  GPIO *port;
};

} // namespace Devices

#endif // SEVENSEGMENT_H_
