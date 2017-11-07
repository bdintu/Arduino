//Pull Up Switch
unsigned char button;
unsigned char state = 0;

typedef struct{
  unsigned char LED;
  unsigned short Time;
  unsigned char Next[8];
} SType;

SType FSM[] = {
  //Botton           0 1 2 3 4 5 6 7            State
  {0b01001100, 2000, {1,0,1,1,1,1,1,1}},         //0 GoW
  {0b01001010, 1000, {2,3,2,2,4,4,4,2}},         //1 WaitW
  {0b01100001, 2000, {3,3,2,3,3,3,3,3}},         //2 GoS
  {0b01010001, 1000, {0,0,1,0,4,4,4,4}},         //3 WaitS
  {0b10001001, 2000, {5,0,2,0,4,5,5,5}},         //4 walk
  {0b10001001, 300, {6,6,6,6,4,6,6,6}},         //5 blink
  {0b00001001, 300, {7,7,7,7,4,7,7,7}},         //6 Unblink
  {0b10001001, 300, {8,8,8,8,4,8,8,8}},         //7 blink
  {0b00001001, 300, {9,9,9,9,4,9,9,9}},         //8 Unblink
  {0b10001001, 300, {10,10,10,4,10,10,10,10}},  //9 blink
  {0b00001001, 300, {0,0,2,0,4,0,2,0}}          //10 Unblink
};

void setup() {
  for(int i=5; i<=12; i++) pinMode(i, OUTPUT);
  Serial.begin(9600);
}

void loop(){

  for(int i=5; i<=12; i++) digitalWrite(i, FSM[state].LED & 0x1<<(i-5));
  delay(FSM[state].Time);

  button = 0;
  for(int i=2; i<=4; i++) button += !digitalRead(i)*0x1<<(i-2);

  state = FSM[state].Next[button];

  Serial.print(state);
  Serial.println(button);
}
