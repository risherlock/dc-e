// TB9051FTG interface for drive-brake (slow decay) operation.
// https://www.pololu.com/product/2997
  
#ifndef _HBRIDGE_H_
#define _HBRIDHE_H_

#include <inttypes.h>

class hbridge
{
private:
  uint8_t pwm_a, pwm_b;

public:
  void init(const uint8_t pin_pwm_a, const uint8_t pin_pwm_b);
  void actuate(const float duty_cycle);
};

#endif

