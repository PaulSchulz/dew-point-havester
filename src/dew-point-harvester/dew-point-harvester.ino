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
const int analog5Pin = 4;
const int analog6Pin = 5;

// State variables:
int serialNumber       = 0;

int coolerCtl          = LOW;
int coolerFanCtl       = LOW;
int coolerPumpCtl      = LOW;
int condenserFanCtl    = LOW;
int condenserPumpCtl   = LOW;

int coolerState        = LOW;
int coolerFanState     = LOW;
int coolerPumpState    = LOW;
int condenserFanState  = LOW;
int condenserPumpState = LOW;
int status1State       = LOW;
int status2State       = LOW;

int   analogResistor1State =    0;
float resistor1Value       =    0;
float temperature1Value    =  999.9;

int   analogResistor2State =    0;
float resistor2Value       =    0;
float temperature2Value    =  999.9;

int   analogResistor3State =    0;
float resistor3Value       =    0;
float temperature3Value    =  999.9;

int   analogResistor4State =    0;
float resistor4Value       =    0;
float temperature4Value    =  999.9;

int   analogResistor5State =    0;
float resistor5Value       =    0;
float temperature5Value    =  999.9;

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
  coolerCtl          = digitalRead(ctlCoolerPin);
  coolerFanCtl       = digitalRead(ctlCoolerFanPin);
  coolerPumpCtl      = digitalRead(ctlCoolerPumpPin);
  condenserFanCtl    = digitalRead(ctlCondenserFanPin);
  condenserPumpCtl   = digitalRead(ctlCoolerPin);

  analogResistor1State = analogRead(analog1Pin);
  analogResistor2State = analogRead(analog2Pin);
  analogResistor3State = analogRead(analog3Pin);
  analogResistor4State = analogRead(analog4Pin);
  analogResistor5State = analogRead(analog5Pin);

  if (coolerCtl == LOW  ){ coolerState = LOW;  }
  if (coolerCtl == HIGH ){ coolerState = HIGH; }

  if (coolerFanCtl == LOW  ){ coolerFanState = LOW;  }
  if (coolerFanCtl == HIGH ){ coolerFanState = HIGH; }

  if (coolerPumpCtl == LOW  ){ coolerPumpState = LOW;  }
  if (coolerPumpCtl == HIGH ){ coolerPumpState = HIGH; }

  if (condenserFanCtl == LOW  ){ condenserFanState = LOW;  }
  if (condenserFanCtl == HIGH ){ condenserFanState = HIGH; }

  if (condenserPumpCtl == LOW  ){ condenserPumpState = LOW;  }
  if (condenserPumpCtl == HIGH ){ condenserPumpState = HIGH; }

  // temperature
  // Get the resistance of the sensor;  
  // Convert to temperature via datasheet;
  resistor1Value
        = (float)(1023-analogResistor1State)*10000/analogResistor1State;
  temperature1Value
        = 1/(log(resistor1Value/10000)/tempCoef+1/298.15)-273.15;

  resistor2Value
        = (float)(1023-analogResistor2State)*10000/analogResistor2State;
  temperature2Value
        = 1/(log(resistor2Value/10000)/tempCoef+1/298.15)-273.15;

  resistor3Value
        = (float)(1023-analogResistor3State)*10000/analogResistor3State;
  temperature3Value
        = 1/(log(resistor3Value/10000)/tempCoef+1/298.15)-273.15;

  resistor4Value
        = (float)(1023-analogResistor4State)*10000/analogResistor4State;
  temperature4Value
        = 1/(log(resistor4Value/10000)/tempCoef+1/298.15)-273.15;

  resistor5Value
        = (float)(1023-analogResistor5State)*10000/analogResistor5State;
  temperature5Value
        = 1/(log(resistor5Value/10000)/tempCoef+1/298.15)-273.15;

  // status
  if( coolerState == HIGH ||
       coolerFanState == HIGH ||
       coolerPumpState == HIGH ){
      status1State = HIGH;  
    } else {
      status1State = LOW; 
    }
      
  if( condenserFanState == HIGH ||
       condenserPumpState == HIGH ){
      status2State = HIGH;
    } else {
      status2State = LOW;
    }

  // output
  digitalWrite(outCoolerPin,        coolerState);  
  digitalWrite(outCoolerFanPin,     coolerFanState);  
  digitalWrite(outCoolerPumpPin,    coolerPumpState);  
  digitalWrite(outCondenserFanPin,  condenserFanState);  
  digitalWrite(outCondenserPumpPin, condenserPumpState);  

  digitalWrite(outStatus1Pin,       status1State);  
  digitalWrite(outStatus2Pin,       status2State);  

  // logging
  Serial.print(serialNumber);
  Serial.print("|");
  Serial.print("|");
  Serial.print(coolerCtl);
  Serial.print("|");
  Serial.print(coolerFanCtl);
  Serial.print("|");
  Serial.print(coolerPumpCtl);
  Serial.print("|");
  Serial.print(condenserFanCtl);
  Serial.print("|");
  Serial.print(condenserPumpCtl);
  Serial.print("|");
  Serial.print("|");
  Serial.print(coolerState);
  Serial.print("|");
  Serial.print(coolerFanState);
  Serial.print("|");
  Serial.print(coolerPumpState);
  Serial.print("|");
  Serial.print(condenserFanState);
  Serial.print("|");
  Serial.print(condenserPumpState);
  Serial.print("|");
  Serial.print(status1State);
  Serial.print("|");
  Serial.print(status2State);
  Serial.print("|");
  Serial.print("|");
  Serial.print(temperature1Value);
  Serial.print("|");
  Serial.print(temperature2Value);
  Serial.print("|");
  Serial.print(temperature3Value);
  Serial.print("|");
  Serial.print(temperature4Value);
  Serial.print("|");
  Serial.print(temperature5Value);
  Serial.print("|");
  Serial.println("");

  delay(loopDelay);

}
