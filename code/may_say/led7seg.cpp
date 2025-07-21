#include "led7seg.h"
#include "Arduino.h"


const int number[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
void showled7seg(int count){
  int digit1 = count / 1000; 
  int digit2 = (count / 100) % 10 ; 
  int digit3 = (count / 10) % 10; 
  int digit4 = count % 10; 
  digitalWrite(seg1, LOW);
  digitalWrite(seg2, HIGH);
  digitalWrite(seg3, HIGH);
  digitalWrite(seg4, HIGH);
  displaynumbers(digit1);
  delay(5);

  digitalWrite(seg1, HIGH);
  digitalWrite(seg2, LOW);
  digitalWrite(seg3, HIGH);
  digitalWrite(seg4, HIGH);
  displaynumbers(digit2);
  delay(5);

  digitalWrite(seg1, HIGH);
  digitalWrite(seg2, HIGH);
  digitalWrite(seg3, LOW);
  digitalWrite(seg4, HIGH);
  displaynumbers(digit3);
  delay(5);

  digitalWrite(seg1, HIGH);
  digitalWrite(seg2, HIGH);
  digitalWrite(seg3, HIGH);
  digitalWrite(seg4, LOW);
  displaynumbers(digit4);
  delay(5);
}

//hien thi cac thanh led
void displaynumbers(int num){
  int segment = number[num];

  digitalWrite(seg_A, (segment & 0x01));
  digitalWrite(seg_B, (segment & 0x02));
  digitalWrite(seg_C, (segment & 0x04));
  digitalWrite(seg_D, (segment & 0x08));
  digitalWrite(seg_E, (segment & 0x10));
  digitalWrite(seg_F, (segment & 0x20));
  digitalWrite(seg_G, (segment & 0x40));
}