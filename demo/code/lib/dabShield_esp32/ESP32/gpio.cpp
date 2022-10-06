#include <stdio.h>
#include <stdint.h>
#include "Arduino.h"
#include "TEA5767Radio.h"
#include "gpio.h"

#define BTN1 32
#define BTN2 35
#define BTN3 34
#define LED  16
#define VR_LEFT   18
#define VR_RIGHT  19

static bool first_run = true;

void gpio_init_io(void)
{
  pinMode(VR_LEFT, INPUT);
  pinMode(VR_RIGHT, INPUT);
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
    Serial.println("btn 1");
  }
  else if(digitalRead(BTN2) == 0)
  {
    delay(30);
    while(digitalRead(BTN2) == 0);
    retVal = is_btn2;
    Serial.println("btn 2");
  }
  else if(digitalRead(BTN3) == 0)
  {
    delay(30);
    while(digitalRead(BTN3) == 0);
    retVal = is_btn3;
    Serial.println("btn 3");
  }

  return retVal;
}

void gpio_read_VR(int8_t *frequency)
{
  int Count = 0;
  static int LeftState = 0;
  static int LeftLastState = 0;

  for(; Count < 2; Count++)
  {
    LeftState = digitalRead(VR_LEFT);
    if (LeftState != LeftLastState) 
    {
      if (digitalRead(VR_RIGHT) != LeftState) 
      {
        if(Count >= 1)
        {
          *frequency += 1;
          if(*frequency > MAX_FRE)
            *frequency = MIN_FRE;
        }
      } 
      else 
      {
        if(Count >= 1)
        {
          *frequency -= 1;
          if(*frequency < MIN_FRE)
            *frequency = MAX_FRE;
        }
      }
    }
    LeftLastState = LeftState;
  }
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
