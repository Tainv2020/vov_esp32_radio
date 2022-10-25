#ifndef _MAX98357_H_
#define _MAX98357_H_

#define I2S_DOUT     25
#define I2S_BCLK     27
#define I2S_LRC      26
#define MAX_CHANNEL  8
#define MIN_CHANNEL  0

const char max98357_channel[MAX_CHANNEL][100] = {"http://media.kythuatvov.vn:7001", \
                                 "http://media.kythuatvov.vn:7003", \
                                 "http://media.kythuatvov.vn:10005", \
                                 "http://media.kythuatvov.vn:7039", \
                                 "http://media.kythuatvov.vn:7007", \
                                 "http://media.kythuatvov.vn:7003", \
                                 "http://media.kythuatvov.vn:7025", \
                                 "http://media.kythuatvov.vn:7021"};

typedef enum
{
  max98357_success = 0,
  max98357_failed
} max98357_status;

max98357_status max98357_wifi_init(void);

void max98357_init(const char add[]);

void max98357_play(void);

void max98357_stop(void);

void max98357_setVolume(uint8_t value);

#endif /* _MAX98357_H_ */
