#include <Arduino.h>
#include "encoder.h"

volatile long encoder::counts = 0;
static int last_encoded = 0;
static long last_count = 0;
static int cpr = 64;

static const int pin_cha = 2;
static const int pin_chb = 3;

// Interrupt handler
void update_encoder()
{
  int msb = digitalRead(pin_cha);
  int lsb = digitalRead(pin_chb);

  int encoded = (msb << 1) | lsb;
  int sum = (last_encoded << 2) | encoded;

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
  {
    encoder::counts++;
  }
  else if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
  {
    encoder::counts--;
  }

  last_encoded = encoded;
}

// Pin and interrupt initializer
void encoder::init(const uint16_t enc_ppr)
{
  cpr = enc_ppr;

  // Pins config
  pinMode(pin_cha, INPUT);
  pinMode(pin_chb, INPUT);

  // Repective interrupt config
  attachInterrupt(0, update_encoder, CHANGE);
  attachInterrupt(1, update_encoder, CHANGE);
}

// Returns angular rate [rad/s]
float encoder::get_omega(const float dt)
{
  // Counts sampled in dt
  long dc = encoder::counts - last_count;
  last_count = encoder::counts;

  // Sampled count to angular rate
  const float r = dc / (float)cpr; // Rotations during dt
  const float f = r / dt;          // Frequency, Hz
  const float w = 2 * M_PI * f;    // Omega, rad/s

  return w;
}

