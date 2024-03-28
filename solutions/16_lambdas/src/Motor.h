// Motor.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#pragma once
#ifndef MOTOR_H
#define MOTOR_H

namespace Devices {
class GPIO;

class Motor {
public:
  Motor(GPIO &gpiod);
  ~Motor();

  void on();
  void off();
  void change_direction();

private:
  GPIO *port;
};

} // namespace Devices

#endif // MOTOR_H_
