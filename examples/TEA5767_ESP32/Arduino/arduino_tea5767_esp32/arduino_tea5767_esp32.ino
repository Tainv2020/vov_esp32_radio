
#include <Wire.h>
#include <LiquidCrystal.h>
#include <stdio.h> 
#define addr 0x60

byte buffer[5];
LiquidCrystal lcd(19, 23, 18, 17, 16, 15);
float frec = 105.3;// write your favorite station here 
int estado1 = 1;
int estado2 = 1;
int button1;
int button2;
 
void setup() {
  // put your setup code here, to run once:
pinMode(14, INPUT_PULLUP);
pinMode(12, INPUT_PULLUP);
Wire.begin();
lcd.begin(16, 2);
lcd.setCursor(4, 0);
lcd.print("RADIO_FM");
lcd.setCursor(10, 1);
lcd.print(" MHz"); 
FM_Set(frec);
print_fm(frec); 
}

void print_fm(float freq1) {
   
   if(frec<=99.9){
   lcd.setCursor(8, 1);
   lcd.print(" "); 
   lcd.setCursor(4, 1);
   lcd.print(freq1,1);  
  }
  else {
   lcd.setCursor(4, 1);
   lcd.print(freq1,1); 
  }
  delay(10);

}
void FM_Set(float freq) {
 
   unsigned int Freq_FM=0; 
   Freq_FM = 4 * (freq * 1000000 + 225000) / 32768;

    buffer[0] = Freq_FM >> 8;
    buffer[1] = Freq_FM & 0XFF;
    buffer[2] = 0xB0;
    buffer[3] = 0x10;
    buffer[4] = 0x00; 

    Wire.beginTransmission(addr);
    Wire.write(buffer[0]);
    Wire.write(buffer[1]);
    Wire.write(buffer[2]);
    Wire.write(buffer[3]);
    Wire.write(buffer[4]);
    Wire.endTransmission();

    delay(10);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  button2=digitalRead(14);
  if(button2==LOW){
    delay(10);
  if(button2==LOW){ 
   estado2 = 0;
   delay(10);    
  }   
 }
 if((button2==HIGH) && (estado2==0)){ //
 
    frec=frec+0.1; 
    if(frec>108.0){  
    frec=88.0;   
   }
   FM_Set(frec);
   print_fm(frec);  
   estado2 = 1;     
 }

  button1=digitalRead(12);
  if(button1==LOW){
    delay(10);
  if(button1==LOW){ 
   estado1 = 0;
   delay(10);    
  }   
 }
 if((button1==HIGH) && (estado1==0)){ // 
 
    frec= frec-0.1; 
    if(frec<88.0){  
    frec=108.0;   
   }
   FM_Set(frec);
   print_fm(frec);
   estado1 = 1;     
 } 
}
