struct{
  int pin;
  int button;
  int state;
  int num;
} a, b;

void setup(){
  a.pin = 12;
  b.pin = 13;

  pinMode(a.pin, INPUT);
  pinMode(b.pin, INPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop(){

  a.button = digitalRead(a.pin);
  b.button = digitalRead(b.pin);
  delay(10);

  if(a.button!=a.state && a.button==0){
    if(a.num==6) a.num = 0;
    a.num++;
    Serial.print("Guess: ");
    Serial.println(a.num);
  }

  if(b.button!=b.state && b.button==0){
    b.num = random(1,7);
    Serial.print("Result: ");
    Serial.println(b.num);
    if(a.num==b.num) Serial.println("You win!");
    else Serial.println("You lose!");

    a.num = 0;
    b.num = 7;
  }

  a.state = a.button;
  b.state = b.button;
}
