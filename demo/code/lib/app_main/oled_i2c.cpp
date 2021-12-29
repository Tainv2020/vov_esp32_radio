#include <stdio.h>
#include <stdint.h>
#include "Arduino.h"
#include <Wire.h>
#include "SSD1306.h"
#include "oled_i2c.h"

/* Initialize the OLED display using Wire library */
SSD1306  display(0x3c, SDA_I2C, SCL_I2C);

void oled_init(void)
{
  display.init();
}

void oled_println(int16_t x, int16_t y, String text)
{
  display.drawString(x, y, text);
  display.display();
}

void oled_clear(void)
{
  display.clear();
}
