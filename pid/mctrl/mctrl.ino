// PID control of BDC motor

#include "pid.h"
#include "tasks.h"
#include "encoder.h"
#include "hbridge.h"

// PID parameters
float set_point = -100;
const unsigned long dt_ms = 20;
float kp = 0.25;
float ki = 0.1;
float umax = 100;
float umin = 0;

// Physical parameters
const int enc_cpr = 64;
const uint8_t pin_pwm_a = 12;
const uint8_t pin_pwm_b = 11;

// Volatiles
volatile bool led_flag = false;
volatile bool pid_flag = false;
volatile bool msg_flag = false;

// Debug messages
const uint16_t dt_factor = 10;
uint16_t dt_count = 0;

// Objects
pid ctrl;
hbridge motor;

void setup()
{
  delay(2000);
  Serial.begin(115200);
  pinMode(13, OUTPUT);

  // PID timing config
  tasks::init_pid_timer(dt_ms);

  // Encoder config
  encoder::init(enc_cpr);

  // PID config
  ctrl.set_kp(kp);
  ctrl.set_ki(ki);
  ctrl.set_control_limits(umin, umax);

  // H-bridge config
   motor.init(pin_pwm_a, pin_pwm_b);
}

void loop()
{
  static float feedback = 0;

  if(pid_flag)
  {
    noInterrupts();
    pid_flag = false;
    interrupts();

    // Sense
    const float dt = dt_ms / 1000.0;
    feedback = encoder::get_omega(dt);

    // Think
    const float error = set_point - feedback;
    const float duty_cycle = ctrl.update(error, dt);

    // Actuate
    motor.actuate(duty_cycle);
  }

  if(msg_flag)
  {
    Serial.print(set_point);
    Serial.print(",");
    Serial.println(feedback);
    msg_flag = false;
  }
}

// Handles PID and message timing
ISR(TIMER3_COMPA_vect)
{
  pid_flag = true;
  digitalWrite(13, led_flag);
  led_flag = !led_flag;

  if(dt_count == dt_factor)
  {
    msg_flag = true;
    dt_count = 0;
  }
  dt_count++;
}

