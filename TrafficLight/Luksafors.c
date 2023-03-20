//Using ESP32 WROOVER DEV KIT
#define coef 2
const int Led_red = 13;
const int Led_yellow = 12;
const int Led_green = 14;
const int Poga = 34;
bool nakts = false;
int ledstate = 0;

void IRAM_ATTR luksaforReset() {//interrupt
  //red+yellow
    digitalWrite(Led_red, HIGH);
    digitalWrite(Led_yellow, HIGH);
    digitalWrite(Led_green, LOW);
    delay(1000*coef);
    //green
    digitalWrite(Led_red, LOW);
    digitalWrite(Led_yellow, LOW);
    digitalWrite(Led_green, HIGH);
    delay(2000*coef);
    //green blink
    digitalWrite(Led_red, LOW);
    digitalWrite(Led_yellow, LOW);
    for(int i = 0; i <6*coef;i++){
      ledstate =! ledstate;
    digitalWrite(Led_green, ledstate);
    delay(200);
    }
    //red
    digitalWrite(Led_red, HIGH);
    digitalWrite(Led_yellow, LOW);
    digitalWrite(Led_green, LOW);
    delay(2000*coef);
}

void setup(){
  Serial.begin(115200); 
  for(int j = 12; j<15;j++){
    pinMode(j,OUTPUT);
  }
//   pinMode(Led_red, OUTPUT);
//   pinMode(Led_yellow, OUTPUT);
//   pinMode(Led_green, OUTPUT);
  pinMode(Poga, INPUT);//pullup
  attachInterrupt(Poga, luksaforReset, FALLING);
  Serial.println("Izvēlieties režīmu: \"diena\" vai \"nakts\"");
}

void loop() {
  if (Serial.available() > 0){
    String Mode = Serial.readStringUntil('\n');
    Mode.trim();
    if (Mode == "diena"){
      nakts = false;
    }
    else if (Mode == "nakts"){
      nakts = true;
    }
    else Serial.println("Lūdzu ievadiet \"diena\" vai \"nakts\"");
  }
  if (nakts == true){
    digitalWrite(Led_red, LOW);
    digitalWrite(Led_yellow, ledstate);
    ledstate =! ledstate;
    digitalWrite(Led_green, LOW);
    delay(200);
  }
  else {
    //red+yellow
    digitalWrite(Led_red, HIGH);
    digitalWrite(Led_yellow, HIGH);
    digitalWrite(Led_green, LOW);
    delay(1000*coef);
    //green
    digitalWrite(Led_red, LOW);
    digitalWrite(Led_yellow, LOW);
    digitalWrite(Led_green, HIGH);
    delay(2000*coef);
    //green blink
    digitalWrite(Led_red, LOW);
    digitalWrite(Led_yellow, LOW);
    for(int i = 0; i <6*coef;i++){
      ledstate =! ledstate;
    digitalWrite(Led_green, ledstate);
    delay(200);
    }
    //red
    digitalWrite(Led_red, HIGH);
    digitalWrite(Led_yellow, LOW);
    digitalWrite(Led_green, LOW);
    delay(2000*coef);
  }
}
