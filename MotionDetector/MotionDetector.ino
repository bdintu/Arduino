#include <math.h>

#define BAUD_RATE 9600
#define VCC_PIN A0
#define GND_PIN A4
#define SND_PIN 11
#define X_AXIS_PIN A1
#define Y_AXIS_PIN A2
#define Z_AXIS_PIN A3
#define NUM_AXES 3
#define BUFFER_SIZE 16

const unsigned int PINS[NUM_AXES] = {X_AXIS_PIN, Y_AXIS_PIN, Z_AXIS_PIN};
int buffer[NUM_AXES][BUFFER_SIZE];
int buffer_pos[NUM_AXES] = { 0 };

void setup(){
  Serial.begin(BAUD_RATE); 
  pinMode(VCC_PIN,OUTPUT);
  pinMode(X_AXIS_PIN,INPUT);
  pinMode(Y_AXIS_PIN,INPUT);
  pinMode(Z_AXIS_PIN,INPUT);
  pinMode(GND_PIN,OUTPUT);

  analogWrite(VCC_PIN,255);
  analogWrite(GND_PIN,0);
}

int get_axis(const int axis){
  delay(1);
  buffer[axis][buffer_pos[axis]] = analogRead(PINS[axis]);
  buffer_pos[axis] = (buffer_pos[axis] + 1) % BUFFER_SIZE;
  long sum = 0;
  for (unsigned int i = 0; i < BUFFER_SIZE; i++) sum += buffer[axis][i];
  return round(sum / BUFFER_SIZE);
}

int get_x() { return get_axis(0); }
int get_y() { return get_axis(1); }
int get_z() { return get_axis(2); }

void snd(){
  static unsigned i = 0;
  Serial.print(i++);
  Serial.println();
  tone(SND_PIN,500);
  delay(500);
  noTone(SND_PIN);
}

void loop() {
  int dif_x = 0;
  int dif_y = 0;
  int dif_z = 0;

  dif_x = get_x();
  dif_y = get_y();
  dif_z = get_z();

  dif_x = abs(get_x() - dif_x);
  dif_y = abs(get_y() - dif_y);
  dif_z = abs(get_z() - dif_z);

  if( dif_x > 5  ||  dif_y > 5  ||  dif_z > 5 ) snd();
}
