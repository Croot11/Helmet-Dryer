#include "led7seg.h"

#define motorPin  19 //chan dong co
#define button    18
#define ledUV     17
#define relay     16
#define ledstatus 23

int thoi_gian = 0;
int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
int flag4 = 0;
int flag5 = 0;
int lasttimer = 0;
int lasttimer1 = 0;
hw_timer_t *timer0 = NULL;
hw_timer_t *timer1 = NULL;
volatile int dutyCycle = 0;      
volatile bool increaseSpeed = true;
volatile unsigned long count = 20;
volatile unsigned long count1 = 0;

void start();
void stop();
void reset_all();
void IRAM_ATTR timer0_ISR(){
  count++;
  count1++;
  Serial.print("Count:");
  Serial.println(count);
  if(thoi_gian > 0 && flag4 == 1 && count1 % 60 == 0){
    thoi_gian--;
    if(thoi_gian == 0){
      flag5 = 1;
    }
  }
}
void IRAM_ATTR timer1_ISR() {
  // Cập nhật giá trị PWM trên chân điều khiển động cơ
  // ledcWrite(0, dutyCycle); // Kênh 0

  // // Tăng dần hoặc giảm dần dutyCycle
  // if (increaseSpeed) {
  //   dutyCycle++;
  //   if (dutyCycle >= 255) {  // Khi đạt đến 100%
  //     increaseSpeed = false;  // Bắt đầu giảm dần
  //   }
  // } else {
  //   dutyCycle--;
  //   if (dutyCycle <= 0) {    // Khi giảm về 0
  //     increaseSpeed = true;   // Bắt đầu tăng lại
  //   }
  // }
}

void setup() {

  Serial.begin(115200);
  //cau hinh cac chan
  pinMode(ledUV, OUTPUT);
  pinMode(ledstatus, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(button, INPUT_PULLUP);

  pinMode(seg_A, OUTPUT);
  pinMode(seg_B, OUTPUT);
  pinMode(seg_C, OUTPUT);
  pinMode(seg_D, OUTPUT);
  pinMode(seg_E, OUTPUT);
  pinMode(seg_F, OUTPUT);
  pinMode(seg_G, OUTPUT);
  pinMode(seg1, OUTPUT);
  pinMode(seg2, OUTPUT);
  pinMode(seg3, OUTPUT);
  pinMode(seg4, OUTPUT);
  //cau hinh timer
  ledcSetup(0, 5000, 8);        
  ledcAttachPin(motorPin, 0);   
  ledcWrite(0, 0);
  //dem thoi gian
  timer0 = timerBegin(0, 80, true);  
  timerAttachInterrupt(timer0, timer0_ISR, true);
  timerAlarmWrite(timer0, 1000000, true);  
  timerAlarmEnable(timer0);
  //bam xung
  timer1 = timerBegin(1, 80, true);  
  timerAttachInterrupt(timer1, timer1_ISR, true);
  timerAlarmWrite(timer1, 10000, true);  
  timerAlarmEnable(timer1);


  //thiet lap muc
  digitalWrite(ledUV, LOW);
  digitalWrite(ledstatus, LOW);
  digitalWrite(relay, LOW);

  digitalWrite(seg_A, HIGH);
  digitalWrite(seg_B, HIGH);
  digitalWrite(seg_C, HIGH);
  digitalWrite(seg_D, HIGH);
  digitalWrite(seg_E, HIGH);
  digitalWrite(seg_F, HIGH); // Sử dụng SEG_F thay vì F
  digitalWrite(seg_G, HIGH);
  digitalWrite(seg1, LOW);
  digitalWrite(seg2, LOW);
  digitalWrite(seg3, LOW);
  digitalWrite(seg4, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  showled7seg(thoi_gian);
  if(digitalRead(button) == 0 && flag1 == 0){
    while(digitalRead(button) == 0);    
    thoi_gian = 5;
    flag1 = 1;
    lasttimer = count;   
    Serial.print("lastimer: "); 
    Serial.println(lasttimer);
  }
  if(digitalRead(button) == 0 && flag1 == 1 && flag2 == 0){
    while(digitalRead(button) == 0);
    thoi_gian = 10;
    lasttimer = count;
    Serial.print("lastimer: "); 
    Serial.println(lasttimer);
    flag2 = 1;
  }
  if(digitalRead(button) == 0 && flag2 == 1 && flag3 == 0){
    while(digitalRead(button) == 0);
    thoi_gian = 15;
    lasttimer = count;
    flag3 = 1;
    Serial.print("lastimer: "); 
    Serial.println(lasttimer);
  }
  if(digitalRead(button) == 0 && thoi_gian == 15 && flag4 == 0){
    while(digitalRead(button) == 0);
    thoi_gian = 0;
    reset_all();
  }
  //cho phep he thong hoat dong
  if((count - lasttimer) > 10 && (count - lasttimer) < 15 && flag4 == 0){
    flag4 = 1;
    count1 = 0;
    start();
    flag2 = 1;
    flag3 = 1;
    
  }
  //stop hoat dong
  // if(flag1 == 1 && flag2 == 0 && flag3 == 0 && flag4 == 1 && count1 > 300){
  //   Serial.println("het 5p");
  //   reset_all();
  //   stop();    
  // }
  // if(flag2 == 1 && flag3 == 0 && flag4 == 1 && count1 > 600){
  //   reset_all();
  //   stop();
  // }
  // if(flag3 == 1 && flag4 == 1 && count1 > 900){
  //   reset_all();
  //   stop();
  // }
  if(digitalRead(button) == 0 && flag4 == 1){
    while(digitalRead(button) == 0);
    reset_all();
    stop();
  }
  if(flag5 == 1){
    reset_all();
    stop();    
  }
  
}


void reset_all(){
  flag1 = 0;
  flag2 = 0;
  flag3 = 0;
  flag4 = 0;
  flag5 = 0;
  count = 15;
  lasttimer = 0;
  lasttimer1 = 0;
  thoi_gian = 0;
}

void start(){
  ledcWrite(0, 255);
  digitalWrite(ledUV, HIGH);
  digitalWrite(ledstatus, HIGH);
  digitalWrite(relay, HIGH);
}

void stop(){
  ledcWrite(0, 0);
  digitalWrite(ledUV, LOW);
  digitalWrite(ledstatus, LOW);
  digitalWrite(relay, LOW);
}


