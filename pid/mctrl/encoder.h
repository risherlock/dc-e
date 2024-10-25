#ifndef _ENCODER_H_
#define _ENCODER_H_

#include <inttypes.h>

namespace encoder
{
  extern volatile long counts;

  float get_omega(const float dt);
  void init(const uint16_t enc_cpr);
  long get_count(void);
}

#endif

