#include <Arduino.h>

int ser1 = 3;           // 舵机初始化
int ser2 = 5;
int ser3 = 6;
int ser4 = 9;
int ser5 = 10;
int ser6 = 11;
  
// 从Nano传回的舵机控制信号的检测IO口
int io1 = 2;
int io2 = 4;
int io3 = 7;
int io4 = 8;
int io5 = 12;
int io6 = 13;

// 爪子收回时舵机的角度
#define ser1In  0
#define ser2In  220
#define ser3In  180
#define ser4In  20
#define ser5In  160
#define ser6In  160

// 爪子伸出时舵机的角度
#define ser1Out 180
#define ser2Out 0
#define ser3Out 0
#define ser4Out 180
#define ser5Out 0
#define ser6Out 0

char nanoFlag[8] = {};
char flag = '0';

// 爪子按编号输出
void ServoAction(){
  if(nanoFlag[1] == '1'){
    analogWrite(ser1,125);
  }else{
    //ser1.write(ser1In);
    analogWrite(ser1,50);
  }
  if(nanoFlag[2] == '1'){
    analogWrite(ser2,125);
  }else{
    analogWrite(ser2,50);
  }
  if(nanoFlag[3] == '1'){
    analogWrite(ser3,125);
  }else{
    analogWrite(ser3,50);
  }
  if(nanoFlag[4] == '1'){
    analogWrite(ser4,125);
  }else{
    analogWrite(ser4,50);
  }
  if(nanoFlag[5] == '1'){
    analogWrite(ser5,125);
  }else{
    analogWrite(ser5,50);
  }
  if(nanoFlag[6] == '1'){
   analogWrite(ser6,125);
  }else{
   analogWrite(ser6,50);
  }
}


void setup(){
  Serial.begin(9600);

  pinMode(io1, INPUT);
  pinMode(io2, INPUT);
  pinMode(io3, INPUT);
  pinMode(io4, INPUT);
  pinMode(io5, INPUT);
  pinMode(io6, INPUT);

  pinMode(ser1, OUTPUT);
  pinMode(ser2, OUTPUT);
  pinMode(ser3, OUTPUT);
  pinMode(ser4, OUTPUT);
  pinMode(ser5, OUTPUT);
  pinMode(ser6, OUTPUT);

  strcpy(nanoFlag, "a000000");
  ServoAction();
}

void loop() 
{
  int i = 0;
//  if(Serial.available()>0) {
//    nanoFlag[i] = Serial.read();
//    if(nanoFlag[i] == 'a'){
//      i++;
//      while((Serial.available() > 0) && (i <= 6)) {
//        nanoFlag[i] = Serial.read();
//        i++;
//        delay(100);
//      }
//      ServoAction();
//      i = 0;
//    }
//  }

  char flag;
  flag = Serial.read();
  if(flag == '1') nanoFlag[1] = '1'; else if(digitalRead(io1) == LOW) nanoFlag[1] = '0';
  if(flag == '2') nanoFlag[2] = '1'; else if(digitalRead(io2) == LOW) nanoFlag[2] = '0';
  if(flag == '3') nanoFlag[3] = '1'; else if(digitalRead(io3) == LOW) nanoFlag[3] = '0';
  if(flag == '4') nanoFlag[4] = '1'; else if(digitalRead(io4) == LOW) nanoFlag[4] = '0';
  if(flag == '5') nanoFlag[5] = '1'; else if(digitalRead(io5) == LOW) nanoFlag[5] = '0';
  if(flag == '6') nanoFlag[6] = '1'; else if(digitalRead(io6) == LOW) nanoFlag[6] = '0';
  
  
//  if(digitalRead(io1) == HIGH) nanoFlag[1] = '1'; else if(digitalRead(io1) == LOW) nanoFlag[1] = '0';
//  if(digitalRead(io2) == HIGH) nanoFlag[2] = '1'; else if(digitalRead(io2) == LOW) nanoFlag[2] = '0';
//  if(digitalRead(io3) == HIGH) nanoFlag[3] = '1'; else if(digitalRead(io3) == LOW) nanoFlag[3] = '0';
//  if(digitalRead(io4) == HIGH) nanoFlag[4] = '1'; else if(digitalRead(io4) == LOW) nanoFlag[4] = '0';
//  if(digitalRead(io5) == HIGH) nanoFlag[5] = '1'; else if(digitalRead(io5) == LOW) nanoFlag[5] = '0';
//  if(digitalRead(io6) == HIGH) nanoFlag[6] = '1'; else if(digitalRead(io6) == LOW) nanoFlag[6] = '0';
  
  ServoAction();
  delay(1000);
  
  Serial.println(nanoFlag);
}
