#include "gpio.h"
#include <Wire.h>
#include "oled_i2c.h"
#include "TEA5767Radio.h"
#include "max98357.h"

TEA5767Radio radio = TEA5767Radio();

static float frequency = 0;
static float frequency_pre = 0;
static float use_max98357 = false;

static void app_set_frequency(float frc);
static void app_display_frc(float frc);

void setup() 
{
  gpio_init_io();
  Serial.begin(115200);
  oled_init();
  Wire.begin();
  radio.setFrequency(DEFAULT_FRC);
  app_display_frc(DEFAULT_FRC);

  frequency = gpio_read_VR();
  frequency_pre = frequency;
}

void loop() 
{
  // frequency = gpio_read_VR();
  
  /* Set frequency through VR */
  if(frequency_pre != frequency)
  {
    frequency_pre = frequency;
    app_set_frequency(frequency);
  }

  gpio_btn check_btn = gpio_check_btn();
  if(check_btn == is_btn1)
  {
    max98357_stop();
    delay(500);
    app_set_frequency(HN_FRC);
  }
  else if(check_btn == is_btn2)
  {
//    app_set_frequency(VOV1_FRC);
    max98357_status stt = max98357_wifi_init();
    if(stt == max98357_success)
    {
      oled_println(10, 50, "Connect to wifi success");
      max98357_init();
    }
    else
    {
      oled_println(10, 50, "Connect to wifi failed");
    }
  }
  else if(check_btn == is_btn3)
  {
    app_set_frequency(VOV2_FRC);
  }

  max98357_play();
}

static void app_set_frequency(float frc)
{
  radio.setFrequency(frc);
  app_display_frc(frc);
}

static void app_display_frc(float frc)
{
  oled_clear();
  oled_println(10, 10, "ESP32 VOV radio");
  oled_println(10, 20, "FRC: " + String(frc));
}
