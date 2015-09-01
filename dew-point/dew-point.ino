/*
 Dew Point Controller

 Turns on and off a Dew Point components
 - Status LEDS

 --- Put Copywrite Notice Here ---
*/

#include <math.h>

// Constants won't change.
// Digital Inputs
const int ctlCoolerPin        =  2;
const int ctlCoolerFanPin     =  3;
const int ctlCoolerPumpPin    =  4;
const int ctlCondenserFanPin  =  5;
const int ctlCondenserPumpPin =  6;
// Outputs
const int outCoolerPin        =  7; 
const int outCoolerFanPin     =  8;
const int outCoolerPumpPin    =  9; // PWM 
const int outCondenserFanPin  = 10; // PWM
const int outCondenserPumpPin = 11; // PWM   
const int outStatus1Pin       = 12;
const int outStatus2Pin       = 13;

// Analog in
const int analog1Pin = 0;
const int analog2Pin = 1;
const int analog3Pin = 2;
const int analog4Pin = 3;

// State variables:
int serialNumber       = 0;

int coolerState        = LOW;
int coolerFanState     = LOW;
int coolerPumpState    = LOW;
int condenserFanState  = LOW;
int condenserPumpState = LOW;
int status1State       = LOW;
int status2State       = LOW;

int   analogResistor1State =    0;
float resister1Value       =    0;
float temperature1Value    =  999.9;
const int tempCoef         = 3975;

const int loopDelay = 1000;

void setup() {
  // system initialisation
  Serial.begin(9600);

  // initialize the input pins:
  pinMode(ctlCoolerPin,        INPUT);     
  pinMode(ctlCoolerFanPin,     INPUT);     
  pinMode(ctlCoolerPumpPin,    INPUT);     
  pinMode(ctlCondenserFanPin,  INPUT);     
  pinMode(ctlCondenserPumpPin, INPUT);     

  // initialize the output pins:
  pinMode(outCoolerPin,        OUTPUT);
  pinMode(outCoolerFanPin,     OUTPUT);  
  pinMode(outCoolerPumpPin,    OUTPUT);  
  pinMode(outCondenserFanPin,  OUTPUT);  
  pinMode(outCondenserPumpPin, OUTPUT);  
  pinMode(outStatus1Pin,       OUTPUT);  
  pinMode(outStatus2Pin,       OUTPUT);  
 
}

void loop(){
  serialNumber = serialNumber+1;
  
  // read the external state
  coolerState          = digitalRead(ctlCoolerPin);
  coolerFanState       = digitalRead(ctlCoolerFanPin);
  coolerPumpState      = digitalRead(ctlCoolerPumpPin);
  condenserFanState    = digitalRead(ctlCondenserFanPin);
  condenserPumpState   = digitalRead(ctlCoolerPin);

  analogResistor1State = analogRead(analog1Pin);

  // temperature
  // Get the resistance of the sensor;  
  resistor1Value
        = (float)(1023-analogResistor1State)*10000/analogResistor1State;
  // Convert to temperature via datasheet;
  temperature1Value
        = 1/(log(resistor1Value/10000)/tempCoef+1/298.15)-273.15;

  // status
  if (ctlCoolerPin == HIGH ||
      ctlCoolerFanPin == HIGH ||
      ctlCoolerPumpPin == HIGH )    { status1State = HIGH; };
      
  if (ctlCondenserFanPin == HIGH ||
      ctlCondenserPumpPin == HIGH ) { status2State = HIGH; };

  // output
  digitalWrite(outCoolerPin,        coolerState);  
  digitalWrite(outCoolerFanPin,     coolerFanState);  
  digitalWrite(outCoolerPumpPin,    coolerPumpState);  
  digitalWrite(outCondenserFanPin,  condenserFanState);  
  digitalWrite(outCondenserPumpPin, condenserPumpState);  

  digitalWrite(outStatus1Pin,       status1State);  
  digitalWrite(outStatus2Pin,       status2State);  

  //logging
  Serial.print(serialNumber);
  Serial.print("|");
  Serial.print(temperature1Value);
  Serial.print("|");
  Serial.println("");

  delay(loopDelay);

}
