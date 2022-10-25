#include <stdio.h>
#include <stdint.h>
#include "Arduino.h"
#include "TEA5767Radio.h"
#include "gpio.h"

#define BTN_NEXT 32
#define BTN_MODE 35
#define BTN_PRE  34
#define LED  16
#define VR_LEFT   18
#define VR_RIGHT  19
#define TIME_MODE 3000

gpio_btn g_btn_state = is_unknow;

void gpio_init_io(void)
{
  pinMode(VR_LEFT, INPUT);
  pinMode(VR_RIGHT, INPUT);
  pinMode(BTN_NEXT, INPUT_PULLUP);
  pinMode(BTN_MODE, INPUT_PULLUP);
  pinMode(BTN_PRE, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  digitalWrite(LED, 1);
}

void gpio_check_btn(void)
{
  unsigned long time_press = 0;

  if(digitalRead(BTN_NEXT) == 0)
  {
    delay(30);
    while(digitalRead(BTN_NEXT) == 0);
    g_btn_state = is_btn_next;
    //Serial.println("btn next");
  }
  else if(digitalRead(BTN_MODE) == 0)
  {
    time_press = millis();
    delay(30);
    while(digitalRead(BTN_MODE) == 0);

    if((unsigned long)(millis() - time_press) >= TIME_MODE)
    {
      g_btn_state = is_btn_mode;
      //Serial.println("btn mode");
    }
    else
    {
      g_btn_state = is_btn_play_stop;
      //Serial.println("play/stop");
    }
  }
  else if(digitalRead(BTN_PRE) == 0)
  {
    delay(30);
    while(digitalRead(BTN_PRE) == 0);
    g_btn_state = is_btn_pre;
    //Serial.println("btn pre");
  }
}

void gpio_read_VR(int8_t *frequency)
{
  int Count = 0;
  static int LeftState = 0;
  static int LeftLastState = 0;

  for(; Count < 2; Count++)
  {
    LeftState = digitalRead(VR_RIGHT);
    if (LeftState != LeftLastState) 
    {
      if (digitalRead(VR_LEFT) != LeftState) 
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
