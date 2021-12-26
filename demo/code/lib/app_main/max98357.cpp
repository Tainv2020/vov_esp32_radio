#include "Arduino.h"
#include "WiFi.h"
#include "Audio.h"
#include "max98357.h"

Audio audio;
String ssid =    "vip 3";
String password = "anhtupkhd";

max98357_status max98357_wifi_init(void)
{
  max98357_status retVal = max98357_success;

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED)
  {
    retVal = max98357_failed;
  }
  delay(1500);

  return retVal;
}

void max98357_init(void)
{
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(100);
  audio.connecttohost("http://vovmedia.vn/vov1?fbclid=IwAR307i7Z11wtzEF1zgiboHxi7bvyPxNzXJTSwsPvOuFQ7UXqDuVrRWxeFYo");
}
