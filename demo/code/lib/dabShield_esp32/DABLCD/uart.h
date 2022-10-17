#ifndef _UART_H_
#define _UART_H_

/*
 * 0001 -> Run radio
 * 0002 -> Mute radio
 * 0003 -> Display channel 1
 * 0004 -> Display channel 2
 * 0005 -> Display channel 3
 * 0006 -> Display channel 4
 * 0007 -> Display channel 5
 * 0008 -> Display channel 6
 * 0009 -> Wifi failed
 * 0010 -> Wifi available
 * 0011 -> UART not available
 */

typedef enum
{
  uart_run_radio = 0,
  uart_mute_radio,
  uart_display_channel_1,
  uart_display_channel_2,
  uart_display_channel_3,
  uart_display_channel_4,
  uart_display_channel_5,
  uart_display_channel_6,
  uart_wifi_failed,
  uart_available,
  uart_not_available
} uart_code;

void UART_Init(void);
uart_code UART_Decode_String(void);
void UART_Transmit(uart_code Data);

#endif /* _UART_H_ */
