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

typedef enum
{
  using_tea5767 = 0,
  using_max98357
} gpio_module_mode;

void gpio_init_io(void);

gpio_btn gpio_check_btn(void);

float gpio_read_VR(void);

void gpio_stauts_module(gpio_module_mode module);

#endif /* _GPIO_H_ */
