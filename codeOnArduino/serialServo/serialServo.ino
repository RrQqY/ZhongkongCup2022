#include <Servo.h>
#include <Arduino.h>

Servo ser1;
Servo ser2;
Servo ser3;
Servo ser4;
Servo ser5;
Servo ser6;

// 从Nano传回的舵机控制信号的检测IO口
int io1 = 8;
int io2 = 9;
int io3 = 10;
int io4 = 11;
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


// 爪子全部伸出
void ServoOut(){
  ser1.write(ser1Out);
  ser2.write(ser2Out);
  ser3.write(ser3Out);
  ser4.write(ser4Out);
  ser5.write(ser5Out);
  ser6.write(ser6Out);
}

// 爪子全部收回
void ServoIn(){
  ser1.write(ser1In);
  ser2.write(ser2In);
  ser3.write(ser3In);
  ser4.write(ser4In);
  ser5.write(ser5In);
  ser6.write(ser6In);
}

// 爪子按编号输出
void ServoAction(){
  if(nanoFlag[1] == '1'){
    ser1.write(ser1Out);
  }else{
    ser1.write(ser1In);
  }
  if(nanoFlag[2] == '1'){
    ser2.write(ser2Out);
  }else{
    ser2.write(ser2In);
  }
  if(nanoFlag[3] == '1'){
    ser3.write(ser3Out);
  }else{
    ser3.write(ser3In);
  }
  if(nanoFlag[4] == '1'){
    ser4.write(ser4Out);
  }else{
    ser4.write(ser4In);
  }
  if(nanoFlag[5] == '1'){
    ser5.write(ser5Out);
  }else{
    ser5.write(ser5In);
  }
  if(nanoFlag[6] == '1'){
    ser6.write(ser6Out);
  }else{
    ser6.write(ser6In);
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
  
  ser1.attach(2);           // 舵机初始化
  ser2.attach(3);
  ser3.attach(4);
  ser4.attach(5);
  ser5.attach(6);
  ser6.attach(7);

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
  if(digitalRead(io1) == HIGH) nanoFlag[1] = '1'; else if(digitalRead(io1) == LOW) nanoFlag[1] = '0';
  if(digitalRead(io2) == HIGH) nanoFlag[2] = '1'; else if(digitalRead(io2) == LOW) nanoFlag[2] = '0';
  if(digitalRead(io3) == HIGH) nanoFlag[3] = '1'; else if(digitalRead(io3) == LOW) nanoFlag[3] = '0';
  if(digitalRead(io4) == HIGH) nanoFlag[4] = '1'; else if(digitalRead(io4) == LOW) nanoFlag[4] = '0';
  if(digitalRead(io5) == HIGH) nanoFlag[5] = '1'; else if(digitalRead(io5) == LOW) nanoFlag[5] = '0';
  if(digitalRead(io6) == HIGH) nanoFlag[6] = '1'; else if(digitalRead(io6) == LOW) nanoFlag[6] = '0';
  
  ServoAction();
  
  Serial.println(nanoFlag);
}
