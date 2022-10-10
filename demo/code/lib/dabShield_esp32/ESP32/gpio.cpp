#include <stdio.h>
#include <stdint.h>
#include "Arduino.h"
#include "gpio.h"

#define BTN_NEXT 32
#define BTN_MODE 35
#define BTN_PRE  34
#define LED  16

void gpio_init_io(void)
{
  pinMode(BTN_NEXT, INPUT_PULLUP);
  pinMode(BTN_MODE, INPUT_PULLUP);
  pinMode(BTN_PRE, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  digitalWrite(LED, 1);
}

gpio_btn gpio_check_btn(void)
{
  gpio_btn retVal = is_unknow;

  if(digitalRead(BTN_NEXT) == 0)
  {
    delay(30);
    while(digitalRead(BTN_NEXT) == 0);
    retVal = is_btn_next;
    Serial.println("btn next");
  }
  else if(digitalRead(BTN_MODE) == 0)
  {
    delay(30);
    while(digitalRead(BTN_MODE) == 0);
    retVal = is_btn_mode;
    Serial.println("btn mode");
  }
  else if(digitalRead(BTN_PRE) == 0)
  {
    delay(30);
    while(digitalRead(BTN_PRE) == 0);
    retVal = is_btn_pre;
    Serial.println("btn pre");
  }

  return retVal;
}

void gpio_stauts_module(gpio_module_mode module)
{
  switch(module)
  {
    case using_tea5767:
    {
      digitalWrite(LED, 0);
      break;
    }
    case using_max98357:
    {
      digitalWrite(LED, 1);
      break;
    }
    default:
      break;
  }
}
