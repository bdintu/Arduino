short input[3];
short stats[3];
short check[3];
short led = 0;

void setup() {
  for(int i=0; i<3; i++) check[i] = 0;
  for(int i=8; i<=10; i++) pinMode(i, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  for(int i=8; i<=10; i++) input[i-8] = digitalRead(i);
  delay(10);
  for(int i=0; i<3; i++){

    if(stats[i]==1 && input[i]==0){

      if(check[i]==1 && led==1){
        check[i] = 0;
        led = 0;
        continue;
      }

      if(check[i]==0 && led==0){
        check[i] = 1;
        led = 1;
      }
    }
  }
  for(int i=0; i<3; i++) stats[i] = input[i];
  digitalWrite(13, led);
}
