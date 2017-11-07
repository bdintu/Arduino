#define pinButton 13
int button, state, lastState=1;

void setup() {
  pinMode(pinButton, INPUT);
  Serial.begin(9600);
}

void loop() {
  button = digitalRead(pinButton);
  delay(10);
  if(button!=lastState && button==0){
    state=!state;
  }
  lastState=button;
}
