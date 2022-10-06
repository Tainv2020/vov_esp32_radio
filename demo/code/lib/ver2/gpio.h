#ifndef _GPIO_H_
#define _GPIO_H_

typedef enum
{
  is_unknow = 0,
  is_btn1,
  is_btn2,
  is_btn3,
  is_btn4,
  is_btn5,
  is_btn6,
  is_btn_next,
  is_btn_pre,
  is_btn_mode
} gpio_btn;

typedef enum
{
  using_tea5767 = 0,
  using_max98357
} gpio_module_mode;

void gpio_init_io(void);

gpio_btn gpio_check_btn(void);

void gpio_read_VR(int8_t *frequency);

void gpio_stauts_module(gpio_module_mode module);

#endif /* _GPIO_H_ */
