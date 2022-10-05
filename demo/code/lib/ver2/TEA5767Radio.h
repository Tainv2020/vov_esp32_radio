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

#ifndef _TEA5767Radio_H_
#define _TEA5767Radio_H_

/* #define MAX_FRE   110
#define MIN_FRE   90 */
#define MAX_FRE   9
#define MIN_FRE   0 
#define DEFAULT_FRC 90.0
#define HN_FRC 102.7
#define VOV1_FRC 97.0
#define VOV2_FRC 96.5
#define MAX_CHANNEL 10

extern float g_fre_arr[MAX_CHANNEL];

void radio_set_freq(float freq);

void radio_mute(void);

void radio_unmute(void);

#endif /* _TEA5767Radio_H_ */
