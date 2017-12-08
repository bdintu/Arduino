#include <Servo.h>

#define SERVO_PIN 3
#define LDR_PIN A0
#define BUTTON_PIN 2
#define LDR_CENTER 300
#define SEG7_PIN 7

Servo servo;

void rotate() {
  servo.write(30);
  delay(80);
  servo.write(90);
  delay(1000);
}

int num_arr[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };

void seg7(int num){
  for(int i=0; i<7; ++i) {
    bool display = (1<<i)&num_arr[num];
    digitalWrite(SEG7_PIN+i, !display); //Common A
  }
}

void setup() {
  Serial.begin(9600);
  for(int i=0; i<7; ++i) {
    pinMode(SEG7_PIN+i, OUTPUT);
  }
  servo.attach(SERVO_PIN);
  servo.write(0);
  delay(500);
}

long time = 0;
long debounce = 200;

int state = LOW;
int reading;
int previous;

int LDRState;
int money = 0;

void loop() {
  LDRState = analogRead(LDR_PIN);
  reading = digitalRead(BUTTON_PIN);

  Serial.print("LDR:");
  Serial.print(LDRState);
  Serial.print(",\tMoney:");
  Serial.print(money);
  Serial.print(",\tState:");
  Serial.print(state);  
  Serial.println();

  if (LDRState >= LDR_CENTER) {
    ++money;
    delay(1000);
  }

  if (reading && !previous && millis() - time > debounce) {
    if (state) {
      state = 0;
    } else {
      state = 1;
    }
    time = millis();
  }

  if (state && money) {
    --money;
    Serial.print("\tmoney:");
    Serial.print(money);
    Serial.println(", Rotate!");
    rotate();
  }

  if (!money) {
    state = 0;
  }
 
  seg7(money);
  previous = reading;
}
