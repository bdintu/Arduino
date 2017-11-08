#define OHM_MAX 10.6
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

float ohm(int value) {
  return (value / 1023.0) * OHM_MAX;
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A2);
  // print out the value you read:
  Serial.print(sensorValue);
  Serial.print(" : ");
  Serial.println(ohm(sensorValue));
  delay(1); // delay in between reads for stability
}
