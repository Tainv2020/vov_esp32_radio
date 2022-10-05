#include <stdio.h>
#include <stdint.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "TFT_LCD.h"

#define _cs   4   // 3 goes to TFT CS
#define _dc   2   // 4 goes to TFT DC
#define _mosi 14  // 5 goes to TFT MOSI
#define _sclk 12  // 6 goes to TFT SCK/CLK
#define _rst  13  // ESP RST to TFT RESET
#define _miso     // Not connected
//       3.3V     // Goes to TFT LED  
//       5v       // Goes to TFT Vcc
//       Gnd      // Goes to TFT Gnd 

Adafruit_ILI9341 tft = Adafruit_ILI9341(_cs, _dc, _mosi, _sclk, _rst);

void TFT_Init()
{
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  
  tft.setTextSize(TFT_SIZE);
  tft.println("VOV radio");
}

void TFT_PrintText(int16_t x, int16_t y, int8_t sizeText, String text)
{
  tft.setCursor(x, y); 
  tft.setTextSize(sizeText);
  tft.println(text);
}

void TFT_DeleteLine(int16_t line)
{
  tft.fillRect(50,line,150,40,ILI9341_BLACK);
}

void TFT_Clear()
{
  tft.fillScreen(ILI9341_BLACK);
  yield();
}
