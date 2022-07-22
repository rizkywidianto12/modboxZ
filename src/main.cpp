#include <Arduino.h>
bool on = 0;
bool firestate = 0;

bool debug = 1;
const int potensio = 1;

const int coil = 4;      // PWM Output ==>>> Gate mosfet
const int ledPin = 2;    // LED indikator
const int fire  = 13;    // Tombol Firing ; D7 nodeMCU
const int up = 14;       // tombol nambah watt
const int don = 12;      // tombol mengurangi watt

int buttonState = 0;         // variable for reading the pushbutton status
int buttonState1 = 0;         // variable for reading the pushbutton status
int pwm =0;
int prestate =0;
int fadeValue = 0;

unsigned ButtonPressCount = 0;
//##############################################
void set() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(up);
  buttonState1 = digitalRead(don);

  if (buttonState == 0 && prestate == 0 && pwm < 11) {
    pwm++;
    digitalWrite(ledPin, 0);
    delay(100);
    // turn LED off
    digitalWrite(ledPin, 1);

    prestate = 1;
  } 
  else if (buttonState1 == 0 && prestate == 0 && pwm > 0) {
    pwm--;
    digitalWrite(ledPin, 0);
    delay(100);
    // turn LED off
    digitalWrite(ledPin, 1);

    prestate = 1;
  } else if(buttonState == 1) {
    prestate = 0;
  }
}
// ##############################################

void poweronoff()
{
  static unsigned long buttonPressTime = 0;


  if (!firestate && !digitalRead(fire) && (millis() - buttonPressTime > 50))
  {
    buttonPressTime = millis();  // Debounce timer start
    ButtonPressCount++;
    Serial.println(F("pressed"));
    Serial.println(ButtonPressCount);
    firestate = 1;
  }
  // else if ((millis()-buttonPressTime >50)) ButtonPressCount = 0;
  else if(firestate && digitalRead(fire)) firestate = 0;
  
  if (ButtonPressCount > 4)
  {
    on = !on;
    ButtonPressCount = 0;
  }
  // else ButtonPressCount = 0;
}



void proses()
{ 
  if(digitalRead(fire)==0){
    analogWrite(coil, fadeValue);
    digitalWrite (ledPin, 0);
  }
  else{
    digitalWrite(coil,0);
    digitalWrite(ledPin,1);
    if(!potensio){
      fadeValue = map(pwm, 0, 10, 0, 255);   // sets the value (range from 0 to 255):
      set();
    }
    else{
      fadeValue = analogRead(A0);   // sets the value (range from 0 to 255):
    }
  }
  // wait for 3 milliseconds to see the dimming effect    
    delay(3);
  }


void setup()  
    { 
     // nothing happens in setup
     if (debug){
      Serial.begin(9600);
     }
  
  analogWriteFreq(1000);
  analogWriteRange(1100);

  pinMode(up, INPUT_PULLUP);
  pinMode(don, INPUT_PULLUP);
  pinMode(fire, INPUT_PULLUP);

  pinMode(A0, INPUT);
  pinMode(coil,1);
  pinMode(ledPin,1);
  } 
 
void loop() {
  proses();
  // poweronoff();


/*
  if(!fire){
    if(!firestate){

    }
    else{
      
    }
  }

  if(on){
    digitalWrite(ledPin,0);
  }
  else{
    digitalWrite(ledPin ,1);
  }
*/
}