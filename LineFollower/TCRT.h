int readIR(){

  real_ir[0] = analogRead(TCRT1);
  real_ir[1] = analogRead(TCRT2);
  real_ir[2] = analogRead(TCRT3);

  for(int i=IR_LEN-1; i>=0; i--){
    if(real_ir[i] > MEAN_IR){
      int_ir[i] = 1;
    }else{
      int_ir[i] = 0;
    }
  }

  Serial.print("real : ");
  Serial.print(real_ir[0]);
  Serial.print(" ");
  Serial.print(real_ir[1]);
  Serial.print(" ");
  Serial.print(real_ir[2]);
  Serial.print(" int : ");
  Serial.print(int_ir[0]);
  Serial.print(" ");
  Serial.print(int_ir[1]);
  Serial.print(" ");
  Serial.print(int_ir[2]);
  Serial.println();
}

/*int meanIR(int mean_ir[]){
  int ir1_b, ir2_b, ir3_b;
  int ir1_w, ir2_w, ir3_w;
 
  ir1_b = analogRead(TCRT1);
  ir2_b = analogRead(TCRT2);
  ir3_b = analogRead(TCRT3);

  motor(50, 50, 50);

  ir1_w = analogRead(TCRT1);
  ir2_w = analogRead(TCRT2);
  ir3_w = analogRead(TCRT3);

  mean_ir[0] = (ir1_b+ir1_w)/2;
  mean_ir[1] = (ir2_b+ir2_w)/2;
  mean_ir[2] = (ir3_b+ir3_w)/2;

#ifdef DEBUG
  Serial.print("mean : ");
  Serial.print(mean_ir[0]);
  Serial.print(" ");
  Serial.print(mean_ir[1]);
  Serial.print(" ");
  Serial.print(mean_ir[2]);
  Serial.println();
#endif
}

int readIR(int mean_ir[]){
  int irsign = 0;
  int real_ir[IR_LEN];
  int int_ir[IR_LEN];
  real_ir[0] = analogRead(TCRT1);
  real_ir[1] = analogRead(TCRT2);
  real_ir[2] = analogRead(TCRT3);

  for(int i=IR_LEN-1; i>=0; i++){
    if(real_ir[i] < mean_ir[i]){
      int_ir[i] = 1;
    }else{
      int_ir[i] = 0;
    }
    irsign += int_ir[i]*(1<<i);
  }

#ifdef DEBUG
  Serial.print("real : ");
  Serial.print(real_ir[0]);
  Serial.print(" ");
  Serial.print(real_ir[1]);
  Serial.print(" ");
  Serial.print(real_ir[2]);
  Serial.print(" int : ");
  Serial.print(int_ir[0]);
  Serial.print(" ");
  Serial.print(int_ir[1]);
  Serial.print(" ");
  Serial.print(int_ir[2]);
  Serial.print(" ");
#endif

  return irsign;
}*/

