#ifndef _OLED_I2C_H_
#define _OLED_I2C_H_

#define SDA_I2C 21
#define SCL_I2C 22

void oled_init(void);

void oled_println(int16_t x, int16_t y, String text);

void oled_clear(void);

#endif /* _OLED_I2C_H_ */
