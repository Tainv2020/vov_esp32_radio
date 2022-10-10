#include "DAB.h"
#include "uart.h"

void setup()
{
  Serial.begin(115200);
  UART_Init();
  DAB_Init();
}

void loop() {
  DAB_Run();
}
