#include "gpio.h"
#include "max98357.h"
#include "uart.h"

static bool g_use_tea5767 = false;
static int add_default = 0;

static void app_init(void);
static bool app_MAX89357_is_ready(void);
static void app_display_max98357(uart_code Data);

void setup() 
{
  /* Init serial */
  Serial.begin(115200);
  app_init();
}

void loop() 
{
  /* Run TEA5767 */
  while(g_use_tea5767)
  {
    /* Check switch mode button */
    if(gpio_check_btn() == is_btn_mode)
    {
      if(app_MAX89357_is_ready())
      {
        g_use_tea5767 = false;
      }
      else
      {
        // display wifi failed on LCD
        app_display_max98357(uart_wifi_failed);
      }
    }
  }

  /* Run MAX89357 */
  while(!g_use_tea5767)
  {
    max98357_play();
    /* Read button */
    gpio_btn check_btn = gpio_check_btn();

    /* Channel down for MAX98357 */
    if(check_btn == is_btn_next)
    {
      if(!g_use_tea5767)
      {
        max98357_status stt = max98357_wifi_init();
        if(stt == max98357_success)
        {
          add_default -= 1;
          if(add_default <= MIN_CHANNEL)
          {
            add_default = MAX_CHANNEL;
          }
          max98357_init(max98357_channel[add_default]);
          app_display_max98357(uart_available);
        }
        else
        {
          // display wifi failed on LCD
          app_display_max98357(uart_wifi_failed);
        }
      }
    }
    /* Channel up for MAX98357 */
    else if(check_btn == is_btn_pre)
    {
      if(!g_use_tea5767)
      {
        max98357_status stt = max98357_wifi_init();
        if(stt == max98357_success)
        {
          add_default += 1;
          if(add_default >= MAX_CHANNEL)
          {
            add_default = MIN_CHANNEL;
          }
          max98357_init(max98357_channel[add_default]);
          app_display_max98357(uart_available);
        }
        else
        {
          // display wifi failed on LCD
          app_display_max98357(uart_wifi_failed);
        }
      }
    }

    /* Check switch mode button */
    if(gpio_check_btn() == is_btn_mode)
    {
      g_use_tea5767 = true;
      /* Stop MAX98357 */
      max98357_stop();
      /* Run radio */
      
    }
  }
}

static void app_init(void)
{
  /* Init I/O */
  gpio_init_io();
  UART_Init();
}

static bool app_MAX89357_is_ready(void)
{
  bool ret_val = false;

  max98357_status stt = max98357_wifi_init();
  if(stt == max98357_success)
  {
    ret_val = true;
    /* MUTE radio */
    
    /* Init MAX98357 */
    max98357_init(max98357_channel[add_default]);
    /* Display channel */
    app_display_max98357(uart_available);
  }
  else
  {
    // display wifi failed on LCD
    app_display_max98357(uart_wifi_failed);
  }

  return ret_val;
}

static void app_display_max98357(uart_code Data)
{
  // Write code to DAB shield to display channel on LCD
  UART_Transmit(Data);
}
