//Chronometer based on 7-segment display model: 5641AS
//Author: V. Nelke
//used english and latvian for naming variables

//DIG1 common Anode - GPIO13
//DIG2 common Anode - GPIO2
//DIG3 common Anode - GPIO0
//DIG4 common Anode - GPIO4
//Letters of the segments:
const int segA = 25;//A - GPIO25
const int segB = 32;//B - GPIO32
const int segC = 22;//C - GPIO22
const int segD = 19;//D - GPIO19
const int segE = 18;//E - GPIO18
const int segF = 33;//F - GPIO33
const int segG = 23;//G - GPIO23
const int segDP = 21;//DP - GPIO21
const int startB = 35;//start
const int holdB = 34;//hold
int reiz_desmit;//factor of 10
int skaits = 0;//Mesurement count
unsigned long long laiks = 0, current_laiks, pedejais_laiks = 0, button_time, last_button_time = 0;
bool runing = false;//run or stop the clock

//interrupt function
//usded for stoping the clock
void IRAM_ATTR ISR(){
  button_time = millis();
  if(button_time - last_button_time >250){//software debounce
    if(skaits == 0) {//Measurement start
      Serial.println("------Mērījumu sākums------");
      Serial.println();
    }
    runing = false;//change the mode
    skaits++;//count the measurement
    //format the number and print it out
    Serial.print("Mērījums Nr.");
    Serial.print(skaits);
    Serial.print(" = ");
    Serial.print(laiks/1000);
    Serial.print(".");
    Serial.print((laiks/100)%10);
    Serial.print((laiks/10)%10);
    Serial.print((laiks)%10);
    Serial.println();
  }
    last_button_time = button_time;//software debounce
}
//pin Setup
void setup() {
  Serial.begin(115200);
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(segDP,OUTPUT);
  pinMode(holdB, INPUT);
  pinMode(startB,INPUT);
  
  pinMode(13,OUTPUT);//DIG1
  pinMode(0,OUTPUT);//DIG2
  pinMode(2,OUTPUT);//DIG3
  pinMode(4,OUTPUT);//DIG4

  attachInterrupt(holdB, ISR, FALLING);
  notirit();//clear all LED's
}

//Main code
void loop() {
  if(digitalRead(startB) == LOW){//start the timer
    runing = true;
  }
  if(runing == true){//counting the current time and displaying it
    current_laiks = millis()- pedejais_laiks;
    reiz_desmit = 10;
    for(int digits = 3;digits>=0;digits--){
      notirit();
      Digit(digits);
      laiks = current_laiks;
      Cipars((laiks/reiz_desmit)%10);
      reiz_desmit = reiz_desmit*10;
      delay(5);
    }
    if (current_laiks >=59999) runing = false;
  }
  if(runing == false){//showing the time at the button press
    reiz_desmit = 10;
    for(int digits = 3;digits>=0;digits--){
      notirit();
      Digit(digits);
      Cipars((laiks/reiz_desmit)%10);
      reiz_desmit = reiz_desmit*10;
      pedejais_laiks = millis();//used to null the timer
      delay(5);
    }
  }
}

//clear function
void notirit(){
  digitalWrite(segA,LOW);
  digitalWrite(segB,LOW);
  digitalWrite(segC,LOW);
  digitalWrite(segD,LOW);
  digitalWrite(segE,LOW);
  digitalWrite(segF,LOW);
  digitalWrite(segG,LOW);
  digitalWrite(segDP,LOW);
  
}

//Choosing a digit
void Digit(int num){
  switch(num){
    case 0:
      digitalWrite(4,LOW);
      digitalWrite(2,LOW);
      digitalWrite(0,LOW);
      digitalWrite(13,HIGH);
      break;
    case 1:
      digitalWrite(2,HIGH);
      digitalWrite(13,LOW);
      digitalWrite(0,LOW);
      digitalWrite(4,LOW);
      digitalWrite(21,HIGH);//decimal point
      break;
    case 2:
      digitalWrite(13,LOW);
      digitalWrite(0,HIGH);
      digitalWrite(2,LOW);
      digitalWrite(4,LOW);
      break;
    case 3:
      digitalWrite(13,LOW);
      digitalWrite(2,LOW);
      digitalWrite(4,HIGH);
      digitalWrite(0,LOW);
      break;
    default: 
      digitalWrite(13,LOW);
      digitalWrite(2,LOW);
      digitalWrite(4,LOW);
      digitalWrite(0,LOW);
  }
}

//Chosing the number 0-9
void Cipars(int cip){
  switch(cip){
    case 0:
      nulle();
      break;
    case 1:
      viens();
      break;
    case 2:
      divi();
      break;
    case 3:
      tris();
      break;
    case 4:
      cetri();
      break;
    case 5:
      pieci();
      break;
    case 6:
      sesi();
      break;
    case 7:
      septini();
      break;
    case 8:
      astoni();
      break;
    case 9:
      devini();
      break;
  }
}

//segment combination for each number
void nulle(){
  //atiecigie LED, lai sanaktu 0
  digitalWrite(segA,HIGH);
  digitalWrite(segB,HIGH);
  digitalWrite(segC,HIGH);
  digitalWrite(segD,HIGH);
  digitalWrite(segE,HIGH);
  digitalWrite(segF,HIGH);
  digitalWrite(segG,LOW);
}
void viens(){
  //atiecigie LED, lai sanaktu 1
  digitalWrite(segA,LOW);
  digitalWrite(segB,HIGH);
  digitalWrite(segC,HIGH);
  digitalWrite(segD,LOW);
  digitalWrite(segE,LOW);
  digitalWrite(segF,LOW);
  digitalWrite(segG,LOW);
}
void divi(){
  //atiecigie LED, lai sanaktu 2
  digitalWrite(segA,HIGH);
  digitalWrite(segB,HIGH);
  digitalWrite(segC,LOW);
  digitalWrite(segD,HIGH);
  digitalWrite(segE,HIGH);
  digitalWrite(segF,LOW);
  digitalWrite(segG,HIGH);
}
void tris(){
  //atiecigie LED, lai sanaktu 3
  digitalWrite(segA,HIGH);
  digitalWrite(segB,HIGH);
  digitalWrite(segC,HIGH);
  digitalWrite(segD,HIGH);
  digitalWrite(segE,LOW);
  digitalWrite(segF,LOW);
  digitalWrite(segG,HIGH);
}
void cetri(){
  //atiecigie LED, lai sanaktu 4
  digitalWrite(segA,LOW);
  digitalWrite(segB,HIGH);
  digitalWrite(segC,HIGH);
  digitalWrite(segD,LOW);
  digitalWrite(segE,LOW);
  digitalWrite(segF,HIGH);
  digitalWrite(segG,HIGH);
}
void pieci(){
  //atiecigie LED, lai sanaktu 5
  digitalWrite(segA,HIGH);
  digitalWrite(segB,LOW);
  digitalWrite(segC,HIGH);
  digitalWrite(segD,HIGH);
  digitalWrite(segE,LOW);
  digitalWrite(segF,HIGH);
  digitalWrite(segG,HIGH);
}
void sesi(){
  //atiecigie LED, lai sanaktu 6
  digitalWrite(segA,HIGH);
  digitalWrite(segB,LOW);
  digitalWrite(segC,HIGH);
  digitalWrite(segD,HIGH);
  digitalWrite(segE,HIGH);
  digitalWrite(segF,HIGH);
  digitalWrite(segG,HIGH);
}
void septini(){
  //atiecigie LED, lai sanaktu 7
  digitalWrite(segA,HIGH);
  digitalWrite(segB,HIGH);
  digitalWrite(segC,HIGH);
  digitalWrite(segD,LOW);
  digitalWrite(segE,LOW);
  digitalWrite(segF,LOW);
  digitalWrite(segG,LOW);
}
void astoni(){
  //atiecigie LED, lai sanaktu 8
  digitalWrite(segA,HIGH);
  digitalWrite(segB,HIGH);
  digitalWrite(segC,HIGH);
  digitalWrite(segD,HIGH);
  digitalWrite(segE,HIGH);
  digitalWrite(segF,HIGH);
  digitalWrite(segG,HIGH);
}
void devini(){
  //atiecigie LED, lai sanaktu 9
  digitalWrite(segA,HIGH);
  digitalWrite(segB,HIGH);
  digitalWrite(segC,HIGH);
  digitalWrite(segD,HIGH);
  digitalWrite(segE,LOW);
  digitalWrite(segF,HIGH);
  digitalWrite(segG,HIGH);
}
