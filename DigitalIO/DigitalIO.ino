const int BUTTON = 8; // the number of the pushbutton pin
const int LED = 7; // the number of the LED pin
int buttonState = 0;
int state = 0;

void setup() {
  // put your setup code here, to run once:
  // initialize the LED pin as an output:
  pinMode(LED, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(BUTTON, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(BUTTON);
  delay(10);
  if (buttonState == HIGH) {
    // turn LED on:
    state = 1 - state;
  }

  if (state == 1) {
    digitalWrite(LED, HIGH);
  } else {
    // turn LED off:
    digitalWrite(LED, LOW);
  }

}
