#include <stdio.h>
#include <stdint.h>
#include "Arduino.h"
#include "gpio.h"

void gpio_init_io(void)
{
  pinMode(VR, INPUT);
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  digitalWrite(LED, 1);
}

gpio_btn gpio_check_btn(void)
{
  gpio_btn retVal = is_unknow;

  if(digitalRead(BTN1) == 0)
  {
    delay(30);
    while(digitalRead(BTN1) == 0);
    retVal = is_btn1;
  }
  else if(digitalRead(BTN2) == 0)
  {
    delay(30);
    while(digitalRead(BTN2) == 0);
    retVal = is_btn2;
  }
  else if(digitalRead(BTN3) == 0)
  {
    delay(30);
    while(digitalRead(BTN3) == 0);
    retVal = is_btn3;
  }

  return retVal;
}

float gpio_read_VR(void)
{
  uint16_t value = 0;
  uint16_t frequency_int = 0;
  float frequency = 0;

  for(int i = 0; i < 10; i++)
  {
     value = value + analogRead(VR);
  }
  
  value = value/10;
  frequency_int = map(value, 0, 4095, 9000, 10700);

  frequency = frequency_int/100.0f;

  return frequency;
}
