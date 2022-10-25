#include <stdio.h>
#include <stdint.h>
#include "Arduino.h"
#include "uart.h"

#define RX2_PIN 16
#define TX2_PIN 17
#define MAX_LENGTH 4
#define MAX_CODE 10

char g_buffer[MAX_LENGTH] = {};

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
  /* Init serial */
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RX2_PIN, TX2_PIN);
}

uart_code UART_Decode_String(void)
{
  uart_code ret_val = uart_not_available;
  
  while(Serial2.available() >= MAX_LENGTH)
  {
    Serial2.readBytes(g_buffer, MAX_LENGTH);

    if(g_buffer[2] == '0')
    {
      switch(g_buffer[3])
      {
        case '1':
        {
          ret_val = uart_run_radio;
          Serial.print("0001");
          break;
        }
        case '2':
        {
          ret_val = uart_mute_radio;
          Serial.print("0002");
          break;
        }
        case '3':
        {
          ret_val = uart_mute_radio;
          Serial.print("0003");
          break;
        }
        case '4':
        {
          ret_val = uart_mute_radio;
          Serial.print("0004");
          break;
        }
        case '5':
        {
          ret_val = uart_mute_radio;
          Serial.print("0005");
          break;
        }
        case '6':
        {
          ret_val = uart_mute_radio;
          Serial.print("0006");
          break;
        }
        case '7':
        {
          ret_val = uart_mute_radio;
          Serial.print("0007");
          break;
        }
        case '8':
        {
          ret_val = uart_mute_radio;
          Serial.print("0008");
          break;
        }
        case '9':
        {
          ret_val = uart_mute_radio;
          Serial.print("0009");
          break;
        }
        default:
          break;
      }
    }
  }

  return ret_val;
}

void UART_Transmit(uart_code Data)
{
  if(Data != uart_not_available)
    Serial2.print(g_data[Data]);
}
