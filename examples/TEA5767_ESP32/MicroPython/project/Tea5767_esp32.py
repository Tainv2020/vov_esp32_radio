from machine import Pin, I2C
from esp32_gpio_lcd import GpioLcd
import time

push1 = Pin(14, Pin.IN, Pin.PULL_UP)
push2 = Pin(12, Pin.IN, Pin.PULL_UP)

frec = 98.8
frec1 = 98
frec2 = 8
std1 = 1
std2 = 1

i2c = I2C(0,scl=Pin(22), sda=Pin(21), freq=400000)
lcd = GpioLcd(rs_pin=Pin(19),
              enable_pin=Pin(23),
              d4_pin=Pin(18),
              d5_pin=Pin(17),
              d6_pin=Pin(16),
              d7_pin=Pin(15),
              num_lines=2, num_columns=16)

lcd.move_to(4,0)
lcd.putstr('RADIO_FM')
time.sleep_ms(10)

def radio_frequency(freq):
    freqB = 4 * (freq * 1000000 + 225000) / 32768
    buf = bytearray(5)
    buf[0] = int(freqB) >> 8
    buf[1] = int(freqB) & 0XFF
    buf[2] = 0X90
    buf[3] = 0X1E
    buf[4] = 0X00
    i2c.writeto(0x60, buf)
    time.sleep_ms(10)

def print_frequency(freq1, freq2):
    lcd.move_to(4,1)
    str_freq = str(freq1) + "." + str(freq2) + " MHZ "
    lcd.putstr(str_freq)
    time.sleep_ms(10)
                  
radio_frequency(frec)
print_frequency(frec1,frec2)

while True:
              
    if push1.value() == 0:
        time.sleep_ms(10)
        if push1.value() == 0:
            std1 = 0
            time.sleep_ms(10)
    if push1.value() == 1 and std1 == 0:
        frec2 = frec2 + 1
        if frec2 > 9:
            frec1 = frec1 + 1
            frec2 = 0
        if frec1 == 108 and frec2==1:
            frec1 = 88
            frec2 = 0
        frec = frec1 + (frec2/10)
        radio_frequency(frec)
        print_frequency(frec1,frec2)
        std1 = 1
        
    if push2.value() == 0:
        time.sleep_ms(10)
        if push2.value() == 0:
            std2 = 0
            time.sleep_ms(10)
    if push2.value() == 1 and std2 == 0:
        frec2 = frec2 - 1
        if frec2 < 0:
            frec1 = frec1 - 1
            frec2 = 9
        if frec1 == 87 and frec2 == 9:
            frec1 = 108
            frec2 = 0
        frec = frec1 + (frec2/10)
        radio_frequency(frec)
        print_frequency(frec1,frec2)
        std2 = 1