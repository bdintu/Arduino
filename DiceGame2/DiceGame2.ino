#define MAX 7

struct{
  int pin;
  int button;
  int state=1;
  int num=0;
} a, b;

int number[10] = {
    0b1000000, //0
    0b1111001, //1  
    0b0100100, //2 
    0b0110000, //3 
    0b0011001, //4
    0b1010010, //5
    0b0000010, //6
    0b1011000, //7
    0b0000000, //8
    0b0010000  //9
};

void showNum(int bin){
  for(int i=2; i<MAX+2; i++){
    digitalWrite(i, bin%2);
    bin/=2;
  }
}

void resetNum(){
  for(int i=2; i<MAX+2; i++){
    digitalWrite(i, 1);
  }
}
  void eff(){
    for(int i=2;i<MAX+1;i++){
      digitalWrite(i, 0);
      delay(100);
      digitalWrite(i, 1);
    }
  }
void win(){
  digitalWrite(10, 1);
  Serial.println("You win!");
  
  showNum(0b0110001);
  delay(1000);
  digitalWrite(11, 0);
  resetNum();
  
}
void lose(){
  digitalWrite(11, 1);
  Serial.println("You lose!");
  showNum(0b0001110);
  delay(1000);
  digitalWrite(11, 0);
  resetNum();
}

void setup(){
  for(int i=2; i<MAX+2; i++){
    pinMode(i, OUTPUT);
  }
  a.pin = 12;
  b.pin = 13;
  pinMode(a.pin, INPUT);
  pinMode(b.pin, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop(){
  digitalWrite(10, 0);
  digitalWrite(11, 0);
  a.button = digitalRead(a.pin);
  b.button = digitalRead(b.pin);
  delay(10);

  if(a.button!=a.state && a.button==0){
    if(a.num==6) a.num = 0;
    a.num++;
    
    Serial.print("Guess: ");
    Serial.println(a.num);
    
    showNum(number[a.num]);
  }

  if(b.button!=b.state && b.button==0){
    b.num = random(1,7);
    
    Serial.print("Result: ");
    Serial.println(b.num);
    
    eff();
    resetNum();
    showNum(number[b.num]);
    eff();
    resetNum();
    if(a.num==b.num)win();
    else lose();
   
    a.num = 0;
    b.num = 7;
  }

  a.state = a.button;
  b.state = b.button;
}
