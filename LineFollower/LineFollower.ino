#include "CONF.h"

  int count=0;
  int irsign = 0;
  int real_ir[IR_LEN];
  int int_ir[IR_LEN];
//int mean_ir[IR_LEN];

#include "L298N.h"
#include "TCRT.h"

void setup(){
  pinMode(TCRT1, INPUT);
  pinMode(TCRT2, INPUT);
  pinMode(TCRT3, INPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  readIR();

  if(count==0){
    count++;
    motor(78,60,50);
  }
  if(int_ir[0] == 1 && int_ir[1] == 1 && int_ir[2] == 1){
    motor(78,60,15);
    if(int_ir[0] == 0 && int_ir[1] == 0 && int_ir[2] == 0){
        motor(72,60,30);
        motor(0,0,10000);
    }
  }
    
  if(int_ir[0] == 0 && int_ir[1] == 1 && int_ir[2] == 0)//010{
    motor(82,60,30);
    Serial.print("eiei");
  }
  
  if(int_ir[0] == 1 && int_ir[1] ==1 /*&& int_ir[2] ==0*/ )//100{
    motor(0,40,10);
  }
  if(/*int_ir[0] == 0  &&*/ int_ir[1] ==1 && int_ir[2] ==1)//001{
    motor(52,0,10);
   }
}
