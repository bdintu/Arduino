#define BAUD_RATE 9600
#define VCC_PIN A0
#define GND_PIN A4
#define BOTT_PIN 2
#define X_AXIS_PIN A1
#define Y_AXIS_PIN A2
#define Z_AXIS_PIN A3
#define NUM_AXES 3
#define BUFFER_SIZE 16

const unsigned int PINS[NUM_AXES] = {X_AXIS_PIN, Y_AXIS_PIN, Z_AXIS_PIN};
int buffer[NUM_AXES][BUFFER_SIZE];
int buffer_pos[NUM_AXES] = { 0 };

int axis_flat[NUM_AXES] = {365, 360, 440};
long sum = 0;

void setup(){
  Serial.begin(BAUD_RATE);
  pinMode(VCC_PIN,OUTPUT);
  pinMode(X_AXIS_PIN,INPUT);
  pinMode(Y_AXIS_PIN,INPUT);
  pinMode(Z_AXIS_PIN,INPUT);
  pinMode(GND_PIN,OUTPUT);
  pinMode(BOTT_PIN, INPUT);
  analogWrite(VCC_PIN,255);
  analogWrite(GND_PIN,0);
}

int get_axis(const int axis){
  delay(1);
  buffer[axis][buffer_pos[axis]] = analogRead(PINS[axis]);
  buffer_pos[axis] = (buffer_pos[axis] + 1) % BUFFER_SIZE;
  sum = 0;
  for (unsigned int i = 0; i < BUFFER_SIZE; i++) sum += buffer[axis][i];
  return round(sum / BUFFER_SIZE);
}

void loop() {

  for(int i = 0; i < 2; i++){
    if( get_axis(i) > axis_flat[i] + 20){
      Serial.print("2 ");
    } else if( get_axis(i) > axis_flat[i] - 20){
      Serial.print("1 ");
    } else {
      Serial.print("0 ");
    }
  }
 
  Serial.println(!digitalRead(BOTT_PIN)+8);
  
  delay(50);
}
