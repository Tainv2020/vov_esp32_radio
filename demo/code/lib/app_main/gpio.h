#ifndef _GPIO_H_
#define _GPIO_H_

#define BTN1 15
#define BTN2 2
#define BTN3 4
#define LED  16
#define VR   34

typedef enum
{
  is_unknow = 0,
  is_btn1,
  is_btn2,
  is_btn3
} gpio_btn;

void gpio_init_io(void);

gpio_btn gpio_check_btn(void);

uint16_t gpio_read_VR(void);

#endif /* _GPIO_H_ */
