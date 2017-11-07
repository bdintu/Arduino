void motor(int inL, int inR, int msec){
    int inv1, inv2, inv3, inv4;
    inL = abs(inL*255/100);
    inR = abs(inR*255/100);

    //Motor Left Forward
    if(inL > 0 && inL <= 100){
        inv1 = 1;
        inv2 = 0;
    }
    //Motor Right Forward
    if(inR > 0 && inR <= 100){
        inv3 = 0;
        inv4 = 1;
    }
  
    if(inL == 0){
            inv1 = 1;
            inv2 = 0;
        }
     //Motor Right Break
     if(inR == 0){
            inv3 = 1;
            inv4 = 0;
     }

    analogWrite(ENA, inL);
    analogWrite(ENB, inR);

    digitalWrite(IN1, inv1);
    digitalWrite(IN2, inv2);
    digitalWrite(IN3, inv3);
    digitalWrite(IN4, inv4);

    delay(msec);
}
