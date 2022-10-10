#include <stdio.h>
#include <stdint.h>
#include "Arduino.h"
#include "uart.h"

#define RX_PIN 2
#define TX_PIN 3
#define MAX_LENGTH 4

char g_buffer[MAX_LENGTH];

void UART_Init(void)
{
  Serial1.begin(9600);
}

uart_decode UART_Decode_String(void)
{
  uart_decode ret_val = uart_not_available;
  
  if(Serial1.available() > MAX_LENGTH)
  {
    Serial1.readBytes(g_buffer, MAX_LENGTH);
    Serial.println(g_buffer);
  }

  return ret_val;
}
