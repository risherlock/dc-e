#include "pid.h"

pid::pid() : kp(0.0), ki(0.0), kd(0.0),
             u_min(0.0), u_max(1.0),
             b(1.0), c(1.0), tf(0.0),
             is_p(false), is_i(false), is_d(false),
             eiz(0.0), edz(0.0), iz(0.0), dz(0.0)
{
}

pid::~pid()
{
}

// Reset PID params
void pid::reset_pid(void)
{
  kp = 0.0, ki = 0.0, kd = 0.0;
  u_min = 0.0, u_max = 1.0;
  b = 1.0, c = 1.0;
  is_p = false, is_i = false, is_d = false;
}

// Rest past memories
void pid::reset_memory(void)
{
  eiz = 0.0; edz = 0.0;
  iz = 0.0; dz = 0.0;
}

// Sign of input number
static int sign(float in)
{
  if (in < 0)
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
float pid::update(const float set_point, const float feedback, const float dt)
{
  const float ep = set_point * b - feedback;
  const float ei = set_point - feedback;
  const float ed = set_point * c - feedback;

  float p = 0.0, i = 0.0, d = 0.0;

  if (is_p)
  {
    p = kp * ep;
  }

  if (is_i)
  {
    i = iz + 0.5 * ki * dt * (ei + eiz);
    iz = i;
    eiz = ei;
  }

  if (is_d)
  {
    d = (-dz * (dt - 2 * tf) + 2 * kd * ed - 2 * kd * edz) / (2 * tf + dt);
    dz = d;
    edz = ed;
  }

  const float u = p + i + d;
  const float u_sat = saturate_control(u);

  return u_sat;
}

void pid::set_limits(const float min, const float max)
{
  if (min < max)
  {
    u_min = min;
    u_max = max;
  }
}
