// SevenSegment.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef SEVENSEGMENT_H
#define SEVENSEGMENT_H

namespace Devices {
class GPIO;

class SevenSegment {
public:
  SevenSegment(GPIO &gpio);
  ~SevenSegment();
  void display(unsigned int value);
  void blank();

private:
  GPIO *port;
};

} // namespace Devices

#endif // SEVENSEGMENT_H_
