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
}

gpio_btn gpio_check_btn(void)
{
  gpio_btn retVal = is_unknow;

  if(digitalRead(BTN1) == 0)
  {
    delay(10);
    while(digitalRead(BTN1) == 0);
    retVal = is_btn1;
  }
  else if(digitalRead(BTN2) == 0)
  {
    delay(10);
    while(digitalRead(BTN2) == 0);
    retVal = is_btn2;
  }
  else if(digitalRead(BTN3) == 0)
  {
    delay(10);
    while(digitalRead(BTN3) == 0);
    retVal = is_btn3;
  }

  return retVal;
}

uint16_t gpio_read_VR(void)
{
  uint16_t retVal = analogRead(VR);

  return retVal;
}
