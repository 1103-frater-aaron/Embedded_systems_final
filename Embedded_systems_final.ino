//Aaron Frater
//libraries
#include <LiquidCrystal.h>
//AS7343 library

// LCD pins    
const int RS = 22, EN = 23, D4 = 24, D5 = 25, D6 = 26, D7 = 27;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
//LED Pins 
const int RedLED = 12, YellowLED = 11, GreenLED = 10, BlueLED = 9;
//Pontentiometer PIN - Analog pin for setting aquarium volume
const int TankSetPin= 0;
// LED for reading the ammonia strip
const int ReadingLEDpin= 8; 
// PINS for the buttons 
const int onButtonPin = 7;
const int offButtonPin = 6;
const int resetButtonPin = 5; 
const int Relay = 4; 

//constants 
const unsigned long ReadingInterval = 15UL * 60 * 1000; // 900,000 ms
const unsigned long bounce= 500; 
//variables
unsigned long lastReadingTime;
unsigned long now;

int gallons=0;
bool on_bounce= false; 
bool on_pressed= false; 
// setting up the states 
bool off_state= true; 
bool on_state = false; 
bool idle_state = false; 
bool error_state = false; 
bool aquarium_calibration= false; 

//enum class State { OFF, IDLE, ACTIVE, ERROR };
//State state = State::OFF;

//volatile bool onPressed = false;


//functions
//void onButtonISR() {
 // onPressed = true;
//}


void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);// move cursor to (0, 0)
  lcd.print("OFF");

  pinMode(onButtonPin, INPUT_PULLUP);
  pinMode(offButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);
  pinMode(RedLED, OUPUT);
  pinMode(YelloLED, OUPUT);
  pinMode(GreenLED, OUPUT);
  pinMode(BlueLED, OUPUT);
  pinMode(Relay,OUPUT);
  pinMode(readingLEDpin, OUPUT);
  lastReadingTime = millis();


  //attachInterrupt(digitalPinToInterrupt(onButtonPin), onButtonISR, FALLING);

  // put your setup code here, to run once:

}

void loop() {
  //noInterrupts();
  //bool onEvent = onPressed;  // Copy the flag set by the ON-button ISR.
  //onPressed = false;          // Clear it for the next press.
  //interrupts();

  //if (onEvent) {
  // Open aquarium-size setup or confirm the selected size.
 // }

// Run the behavior for the current state here.


  while(off_state){
    lcd.clear();
    lcd.setCursor(0, 0);// move cursor to (0, 0)
    lcd.print("OFF");
    digitalWrite(RedLED,HIGH);
    if(digitalRead(onButtonPin)==LOW && (millis()-now)>=bounce){
      now=millis();
      off_state=false; 
      idle_state= true; 
      aquarium_calibration= true; 
    }
    return;

  }
  while(idle_state){
    digitalWrite(YellowLED,HIGH);
    if(aquarium_calibration==true){
      lcd.clear();
      lcd.setCursor(0, 0);// move cursor to (0, 0)
      lcd.print("OFF");

      gallons = map(analogRead(A0), 0, 1023, 1, 120);
      //function conversion from voltage to volume 
      lcd.setCursor(0,1);
      lcd.print(gallons);
      Serial.println(gallons);
      //function that will print out the volume on the LCD 
      //LCD also displays enter volume and then press on button 
      if(digitalRead(onButtonPin)==LOW){
        aquarium_calibration==false);
        return;
      }
    }
    else{
      now = millis();
      if (now - lastReadingTime >= ReadingInterval) {
        lastReadingTime = now;
        Serial.println("15 minutes have passed.");
      }
      //read the light sensor every 15 minutes 
    }

  }


