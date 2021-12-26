#include "gpio.h"
#include <Wire.h>
#include "oled_i2c.h"
#include "TEA5767Radio.h"
#include "max98357.h"

TEA5767Radio radio = TEA5767Radio();

void setup() 
{
  gpio_init_io();
  oled_init();
  Wire.begin();
  radio.setFrequency(102.8);
  max98357_wifi_init();
  max98357_init();
 
  gpio_read_VR();
  gpio_check_btn();
}

void loop() 
{

}
