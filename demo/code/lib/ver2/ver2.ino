#include "gpio.h"
#include <Wire.h>
#include "TEA5767Radio.h"
#include "max98357.h"
#include "TFT_LCD.h"

/* static float frequency = DEFAULT_FRC;
static float frequency_pre; */
static int8_t frequency = 0;
static int8_t frequency_pre = 0;
static bool g_use_tea5767 = true;
static int add_default = 0;
static bool g_radio_isRunning = true;
static bool g_max89357_isRunning = false;

static void app_init(void);
static bool app_MAX89357_is_ready(void);
/* static void app_set_frequency(float frc); */
static void app_set_frequency(float frc);
static void app_display_max98357(void);

void setup() 
{
  /* Init serial */
  Serial.begin(115200);
  app_init();
  app_set_frequency(DEFAULT_FRC);
}

void loop() 
{
  /* Run TEA5767 */
  while(g_use_tea5767)
  {
    /* Read button */
    gpio_check_btn();
    /* Read VR */
    gpio_read_VR(&frequency);

    if(frequency_pre != frequency)
    {
      frequency_pre = frequency;
      //Serial.println(g_fre_arr[frequency]);
      app_set_frequency(g_fre_arr[frequency]);
    }

    /* Check switch mode button */
    if(g_btn_state == is_btn_mode)
    {
      g_btn_state = is_unknow;
      Serial.println("btn mode");
      if(app_MAX89357_is_ready())
      {
        g_use_tea5767 = false;
      }
      else
      {
        TFT_PrintText(0, TFT_LINE_3, TFT_SIZE, "Wifi failed");
      }
    }
    else if(g_btn_state == is_btn_play_stop)
    {
      g_btn_state = is_unknow;
      //Serial.println("play/stop");
      if(g_radio_isRunning)
      {
        radio_mute();
        g_radio_isRunning = false;
      }
      else
      {
        radio_unmute();
        g_radio_isRunning = true;
      }
    }
  }

  /* Run MAX89357 */
  while(!g_use_tea5767)
  {
    if(!g_max89357_isRunning)
    {
      max98357_play();
    }
    /* Read button */
    gpio_check_btn();

    /* Channel down for MAX98357 */
    if(g_btn_state == is_btn_next)
    {
      g_btn_state = is_unknow;
      //Serial.println("btn down");
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
          app_display_max98357();
        }
        else
        {
          TFT_PrintText(0, TFT_LINE_3, TFT_SIZE, "Wifi failed");
        }
      }
    }
    /* Channel up for MAX98357 */
    else if(g_btn_state == is_btn_pre)
    {
      g_btn_state = is_unknow;
      //Serial.println("btn next");
      if(!g_use_tea5767)
      {
        max98357_status stt = max98357_wifi_init();
        if(stt == max98357_success)
        {
          add_default -= 1;
          if(add_default < MIN_CHANNEL)
          {
            add_default = MAX_CHANNEL - 1;
          }
          max98357_init(max98357_channel[add_default]);
          app_display_max98357();
        }
        else
        {
          TFT_PrintText(0, TFT_LINE_3, TFT_SIZE, "Wifi failed");
        }
      }
    }

    /* Check switch mode button */
    if(g_btn_state == is_btn_mode)
    {
      g_btn_state = is_unknow;
      //Serial.println("btn mode");
      g_use_tea5767 = true;
      /* Stop MAX98357 */
      max98357_stop();
      /* Unmute TEA5767 */
      radio_unmute();
      delay(500);
      /* Display frequency on oled */
      app_set_frequency(frequency);
    }
    else if(g_btn_state == is_btn_play_stop)
    {
      g_btn_state = is_unknow;
      //Serial.println("play/stop");
      if(g_max89357_isRunning)
      {
        max98357_stop();
        g_max89357_isRunning = false;
      }
      else
      {
        max98357_play();
        g_max89357_isRunning = true;
      }
    }
  }
}

static void app_init(void)
{
  /* Init I/O */
  gpio_init_io();
  /* Init TFT */
  TFT_Init();
  Wire.begin();
}

static bool app_MAX89357_is_ready(void)
{
  bool ret_val = false;

  max98357_status stt = max98357_wifi_init();
  if(stt == max98357_success)
  {
    ret_val = true;
    /* MUTE TEA5767 */
    radio_mute();
    /* Init MAX98357 */
    max98357_init(max98357_channel[add_default]);
    /* Display channel */
    app_display_max98357();
  }
  else
  {
    TFT_PrintText(0, TFT_LINE_3, TFT_SIZE, "Wifi failed");
  }

  return ret_val;
}

static void app_set_frequency(float frc)
{
  radio_set_freq(frc);
  TFT_DeleteLine(TFT_LINE_2);
  TFT_DeleteLine(TFT_LINE_3);
  TFT_PrintText(0, TFT_LINE_1, TFT_SIZE, "VOV radio");
  TFT_PrintText(0, TFT_LINE_2, TFT_SIZE, "FRC: " + String(frc));
}

static void app_display_max98357(void)
{
  TFT_DeleteLine(TFT_LINE_2);
  TFT_DeleteLine(TFT_LINE_3);
  TFT_PrintText(0, TFT_LINE_1, TFT_SIZE, "VOV radio");
  TFT_PrintText(0, TFT_LINE_2, TFT_SIZE, "Channel: " + String(add_default));
  TFT_PrintText(0, TFT_LINE_3, TFT_SIZE, "Wifi success");
}
