#include <Arduino.h>
#include "hbridge.h"

void hbridge::init(const uint8_t pin_pwm_a, const uint8_t pin_pwm_b)
{
  pwm_a = pin_pwm_a;
  pwm_b = pin_pwm_b;
  pinMode(pwm_a, OUTPUT);
  pinMode(pwm_b, OUTPUT);
}

void hbridge::actuate(const float duty_cycle)
{
  const uint8_t pwm = (uint8_t)fabs(duty_cycle * 2.55f);

  if (duty_cycle < 0.0)
  {
    analogWrite(pwm_a, pwm);
    analogWrite(pwm_b, 0);
  }
  else
  {
    analogWrite(pwm_a, 0);
    analogWrite(pwm_b, pwm);
  }
}

