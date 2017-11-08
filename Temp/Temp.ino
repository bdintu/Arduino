#define LM35_PIN A0
#define MV_MAX 4460
#define T_MAX 34
#define T_MIN 23
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  pinMode(LM35_PIN, INPUT);
  for (int i = 2; i <= 7; ++i) {
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);
}

float mv(int value) {
  return (value / 1023.0) * MV_MAX;
}

float c(int value) {
  return mv(value) / 10;
}

void led(int LEDState) {
  for (int i = 2; i <= LEDState; ++i) {
    digitalWrite(i, HIGH);
  }
  for (int i = LEDState + 1; i <= 7; ++i) {
    digitalWrite(i, LOW);
  }
}

int sensorValue;
float temp;
int LEDState = -1;
int tempState;
float bound = (T_MAX - T_MIN) / 6.0;

void loop() {

  sensorValue = analogRead(LM35_PIN);
  temp = c(sensorValue);
  tempState = ((temp - T_MIN) / bound) + 1;

  Serial.print("val:");
  Serial.print(sensorValue);
  Serial.print(", temp:");
  Serial.print(temp);
  Serial.print("pin:");
  Serial.print(tempState);
  Serial.println();

  if (LEDState != tempState) {
    LEDState = tempState;
  }
  led(LEDState);
  delay(500);
}
