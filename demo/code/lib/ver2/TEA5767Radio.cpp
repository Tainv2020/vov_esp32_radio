/*
TEA5767 I2C FM Radio Library

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

The latest version of this library can always be found at
http://arduiniana.org.


Simon Monk 2013
*/

#include <Arduino.h>
#include <Wire.h>
#include "TEA5767N.h"
#include "TEA5767Radio.h"

float g_fre_arr[MAX_CHANNEL] = {91.0, 94.0, 96.5, 97.0, 102.7, 105.5};
TEA5767N radio = TEA5767N();

void radio_set_freq(float freq)
{
  radio.selectFrequency(freq);
}

void radio_mute(void)
{
  radio.mute();
  radio.setStandByOn();
}

void radio_unmute(void)
{
  radio.turnTheSoundBackOn();
  radio.setStandByOff();
}
