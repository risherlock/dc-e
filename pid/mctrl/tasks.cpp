#include<Arduino.h>
#include "tasks.h"

void tasks::init_pid_timer(unsigned long dt_ms)
{
  noInterrupts();
  TCCR3A = 0;
  TCCR3B = 0;
  TCNT3 = 0;
  
  uint16_t prescaler = 1024;
  uint32_t ocr_val = (16000000UL / (prescaler * (1000.0 / dt_ms))) - 1;
 
  OCR3A = (uint16_t)ocr_val;
  TCCR3A |= 0x00;
  TCCR3B |= (1 << WGM32) | (1 << CS32) | (1 << CS30);
  TIMSK3 |= (1 << OCIE3A);
  interrupts();
}

