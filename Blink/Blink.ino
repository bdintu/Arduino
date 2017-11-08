void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void high(int t) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(t);
}

void low(int t) {
  digitalWrite(LED_BUILTIN, LOW);
  delay(t);
}

void loop() {
  high(1000);
  low(500);
  high(500);
  low(1000);
}
