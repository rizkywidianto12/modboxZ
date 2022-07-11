#include <Arduino.h>

const int coil = 4;      // PWM Output ==>>> Gate mosfet
const int ledPin = 2;    // LED indikator
const int fire  = 13;    // Tombol Firing
const int up = 14;       // tombol nambah watt
const int don = 12;      // tombol mengurangi watt

//##############################################

int buttonState = 0;         // variable for reading the pushbutton status
int buttonState1 = 0;         // variable for reading the pushbutton status
int pwm =0;
int prestate =0;

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
//##############################################

void setup()  
    { 
     // nothing happens in setup 
  pinMode(up, INPUT_PULLUP);
  pinMode(don, INPUT_PULLUP);
  pinMode(fire, INPUT_PULLUP);
  pinMode(coil,1);
  pinMode(ledPin,1);
    } 
 
void loop() 
    { 
      int fadeValue = map(pwm, 0, 10, 0, 255);   // sets the value (range from 0 to 255):
      if(digitalRead(fire)==0){
        analogWrite(coil, fadeValue);
        analogWrite(ledPin, fadeValue);
      }
      else{
        digitalWrite(coil,0);
        digitalWrite(ledPin,1);
        set();
      }
      // wait for 30 milliseconds to see the dimming effect    
      delay(30);                            
    }

    