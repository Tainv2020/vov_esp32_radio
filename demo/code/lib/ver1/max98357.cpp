#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "Arduino.h"
#include "WiFi.h"
#include "Audio.h"
#include "max98357.h"

Audio audio;
String ssid =    "WiFi 101";
String password = "123456789";

static bool max98357_wifi_status(void);

max98357_status max98357_wifi_init(void)
{
  uint8_t counter = 0;
  max98357_status retVal = max98357_failed;

  if(max98357_wifi_status())
  {
    retVal = max98357_success;
  }
  else
  {
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    for(counter = 0; counter < 6; counter ++)
    {
      if(WiFi.status() == WL_CONNECTED)
      {
        retVal = max98357_success;
        break;
      }
      delay(500);
    }
    delay(1500);
  }

  return retVal;
}

void max98357_init(const char add[])
{
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  max98357_setVolume(100);
  audio.connecttohost(add);
  audio.loop();
}

void max98357_play(void)
{
  audio.loop();
}

void max98357_stop(void)
{
  audio.stopSong();
}

void max98357_setVolume(uint8_t value)
{
  audio.setVolume(value); // 0...21
}

static bool max98357_wifi_status(void)
{
  bool retVal = true;

  if(WiFi.status() != WL_CONNECTED)
  {
    retVal = false;
  }

  return retVal;
}
