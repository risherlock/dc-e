#include "pid.h"

pid::pid()
{
}

pid::~pid()
{
}

void pid::reset_memory(void)
{
  ez = 0.0;
  iz = 0.0;
  dz = 0.0;
}

// Sign of input number
static int sign(float in)
{
  if(in < 0)
  {
    return -1;
  }
  else
  {
    return 1;
  }
}

float pid::saturate_control(const float in)
{
  float out = in;

  if (fabs(in) < u_min)
  {
    out = sign(in) * u_min;
  }
  else if (fabs(in) > u_max)
  {
    out = sign(in) * u_max;
  }

  return out;
}

/*           ______________________
            |                      |
  E(s) ---->| kp + ki / s + kd * s |----> U(s)
            |______________________|
*/
float pid::update(float e, float dt)
{
  float p = 0.0, i = 0.0, d = 0.0;

  if (is_p)
  {
    p = kp * e;
  }

  if (is_i)
  {
    i = iz + 0.5 * ki * dt * (e + ez);
    iz = i;
  }

  if (is_d)
  {
    d = -dz + 2 * kd * (e - ez) / dt;
    dz = d;
  }

  const float u = p + i + d;
  ez = e;

  return saturate_control(u);
}

void pid::set_kp(const float p)
{
  kp = p;
  is_p = true;
}

void pid::set_ki(const float i)
{
  ki = i;
  is_i = true;
}

void pid::set_kd(const float d)
{
  kd = d;
  is_d = true;
}

void pid::set_control_limits(const float min, const float max)
{
  if (min < max)
  {
    u_min = min;
    u_max = max;
  }
}
