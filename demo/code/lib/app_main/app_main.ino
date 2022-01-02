#include "gpio.h"
#include <Wire.h>
#include "oled_i2c.h"
#include "TEA5767Radio.h"
#include "max98357.h"

static float frequency = 0.0;
static float frequency_pre = 0.0;
static bool g_use_tea5767 = true;
static uint8_t add_default = 0;

static void app_set_frequency(float frc);
static void app_display_tea5767(float frc);
static void app_display_max98357(void);

void setup() 
{
  gpio_init_io();
  Serial.begin(115200);
  oled_init();
  Wire.begin();
  radio_set_freq(DEFAULT_FRC);
  app_display_tea5767(DEFAULT_FRC);

  frequency = gpio_read_VR();
  frequency_pre = frequency;
}

void loop() 
{
  if(g_use_tea5767)
  {
    frequency = gpio_read_VR();
    
    /* Set frequency through VR */
    if((frequency - frequency_pre >= 0.1f) || (frequency_pre - frequency >= 0.1f))
    {
      frequency_pre = frequency;
      app_set_frequency(frequency);
    }
    delay(50);
  }

  gpio_btn check_btn = gpio_check_btn();
  if(check_btn == is_btn1)
  {
    Serial.println("btn 1");

    /* Switch to MAX98357 */
    if(g_use_tea5767)
    {
      max98357_status stt = max98357_wifi_init();
      if(stt == max98357_success)
      {
        g_use_tea5767 = false;
        radio_mute();
        
        max98357_init(max98357_channel[add_default]);
        app_display_max98357();
      }
      else
      {
        oled_println(10, 50, "Connect to wifi failed");
      }
    }
    /* Switch to TEA5767 */
    else
    {
      g_use_tea5767 = true;
      max98357_stop();
      radio_unmute();
      delay(500);
      app_set_frequency(frequency);
    }
    
  }
  else if(check_btn == is_btn2)
  {
    Serial.println("btn 2");
  }
  else if(check_btn == is_btn3)
  {
    Serial.println("btn 3");
    if(!g_use_tea5767)
    {
      max98357_status stt = max98357_wifi_init();
      if(stt == max98357_success)
      {
        add_default += 1;
        if(add_default >= MAX_CHANNEL)
        {
          add_default = 0;
        }
        Serial.println(max98357_channel[add_default]);
        max98357_init(max98357_channel[add_default]);
        app_display_max98357();
      }
      else
      {
        oled_println(10, 50, "Connect to wifi failed");
      }
    }
  }

  max98357_play();
}

static void app_set_frequency(float frc)
{
  radio_set_freq(frc);
  app_display_tea5767(frc);
}

static void app_display_tea5767(float frc)
{
  oled_clear();
  oled_println(10, 0, "ESP32 VOV radio");
  oled_println(10, 20, "FRC: " + String(frc));
}

static void app_display_max98357(void)
{
  oled_clear();
  oled_println(10, 10, "ESP32 VOV radio");
  oled_println(10, 20, "Channel: " + String(add_default));
  oled_println(10, 50, "Connect to wifi success");
}
