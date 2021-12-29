#ifndef _MAX98357_H_
#define _MAX98357_H_

#define I2S_DOUT     25
#define I2S_BCLK     27
#define I2S_LRC      26

typedef enum
{
  max98357_success = 0,
  max98357_failed
} max98357_status;

max98357_status max98357_wifi_init(void);

void max98357_init(void);

void max98357_play(void);

void max98357_stop(void);

void max98357_setVolume(uint8_t value);

#endif /* _MAX98357_H_ */
