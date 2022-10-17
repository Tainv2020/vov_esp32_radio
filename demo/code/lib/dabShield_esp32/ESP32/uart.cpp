#include <stdio.h>
#include <stdint.h>
#include "Arduino.h"
#include "uart.h"

#define RX_PIN 2
#define TX_PIN 3
#define MAX_LENGTH 4
#define MAX_CODE 10

char g_buffer[MAX_LENGTH];

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
char g_data[MAX_CODE][10] = {"0001", \
                             "0002", \
                             "0003", \
                             "0004", \
                             "0005", \
                             "0006", \
                             "0007", \
                             "0008", \
                             "0009", \
                             "0010", \
                            };

void UART_Init(void)
{
  Serial1.begin(9600);
}

uart_code UART_Decode_String(void)
{
  uart_code ret_val = uart_not_available;
  
  if(Serial1.available() > MAX_LENGTH)
  {
    Serial1.readBytes(g_buffer, MAX_LENGTH);
    Serial.println(g_buffer);
  }

  return ret_val;
}

void UART_Transmit(uart_code Data)
{
  Serial1.print(g_data[Data]);
}
