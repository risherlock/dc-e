#ifndef _PID_H_
#define _PID_H_

#include <math.h>

class pid
{
private:
  // Internal variables
  bool is_p, is_i, is_d; // Enable flags
  float epz, eiz, edz;   // Past errors
  float iz, dz;          // Past I and D

  // Configurable variables
  float kp, ki, kd;   // PID gains
  float u_min, u_max; // Output limits
  float b, c;         // Set-point weights

  float saturate_control(const float in);

public:
  pid();
  ~pid();

  void set_kp(const float val) { kp = val; is_p = true; }
  void set_ki(const float val) { ki = val; is_i = true; }
  void set_kd(const float val) { kd = val; is_d = true; }
  void set_b(const float val) { b = val; }
  void set_c(const float val) { c = val; }

  float get_kp(void) const { return kp; }
  float get_ki(void) const { return ki; }
  float get_kd(void) const { return kd; }
  float get_b(void) const { return b; }
  float get_c(void) const { return c; }

  void reset_pid(void);
  void reset_memory(void);
  float update(const float, const float, const float);
  void set_limits(const float u_min, const float u_max);
};

#endif // pid.h
