/*
 Dew Point Controller

 Turns on and off a Dew Point components
 - Status LEDS

 --- Put Copywrite Notice Here ---
*/

// Constants won't change.
// Digital Inputs
const int ctlCoolerPin        = 2;
const int ctlCoolerFanPin     = 3;
const int ctlCoolerPumpPin    = 4;
const int ctlCondenserFanPin  = 5;
const int ctlCondenserPumpPin = 6;
// Outputs
const int outCoolerPin        = 7; 
const int outCoolerFanPin     = 8;
const int outCoolerPumpPin    = 9;  // PWM 
const int outCondenserFanPin  = 10; // PWM
const int outCondenserPumpPin = 11; // PWM   
const int outStatus1          = 12;
const int outStatus2          = 13;

// Analog in

// State variables:
int coolerState        = LOW;
int coolerFanState     = LOW;
int coolerPumpState    = LOW;
int condenserFanState  = LOW;
int condenserPumpState = LOW;
int status1State       = LOW;
int status2State       = LOW;

void setup() {
  // initialize the input pins:
  pinMode(ctlCoolerPin,        INPUT);     
  pinMode(ctlCoolerFanPin,     INPUT);     
  pinMode(ctlCoolerPumpPin,    INPUT);     
  pinMode(ctlCondenserFanPin,  INPUT);     
  pinMode(ctlContenserPumpPin, INPUT);     

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
  // read the state of the controls:
  coolerState        = digitalRead(CtlCoolerPin);
  coolerFanState     = digitalRead(CtlCoolerFanPin);
  coolerPumpState    = digitalRead(CtlCoolerPumpPin);
  condenserFanState  = digitalRead(CtlCondenserCoolerPin);
  condenserPumpState = digitalRead(CtlCoolerPin);

  // Status
  if (ctlCoolerPin == HIGH)        { coolerState = HIGH };    
  if (ctlCoolerPin == LOW)         { coolerState = LOW };    

  if (ctlCoolerFanPin == HIGH)     { coolerFanState = HIGH };    
  if (ctlCoolerFanPin == LOW)      { coolerFanState = LOW };    

  if (ctlCoolerPumpPin == HIGH)    { coolerPumpState = HIGH };    
  if (ctlCoolerPumpPin == LOW)     { coolerPumpState = LOW };    

  if (ctlCondenserFanPin == HIGH)  { condenserFanState = HIGH };    
  if (ctlCondenserFanPin == LOW)   { condenserFanState = LOW };    

  if (ctlCondenserPumpPin == HIGH) { condenserPumpState = HIGH };    
  if (ctlCondenserPumpPin == LOW)  { condenserPumpState = LOW };    

  // control
  if (ctlCoolerPin == HIGH ||
      ctlCoolerFanPin == HIGH ||
      ctlCoolerPumpPin == HIGH )    { status1State == HIGH };
      
  if (ctlCondenserFanPin == HIGH ||
      ctlCondenserPumpPin == HIGH ) { status2State == HIGH };

  // output
  digitalWrite(outCoolerPin,        coolerState);  
  digitalWrite(outCoolerFanPin,     coolerFanState);  
  digitalWrite(outCoolerPumpPin,    coolerPumpState);  
  digitalWrite(outCondenserFanPin,  condenserFanState);  
  digitalWrite(outCondenserPumpPin, condenserPumpState);  

  digitalWrite(outStatus1Pin,       status1State);  
  digitalWrite(outStatus2Pin,       status2State);  

}
