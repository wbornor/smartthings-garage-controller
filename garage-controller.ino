//*****************************************************************************
#include <SoftwareSerial.h>   

#define PIN_LED           13
#define PIN_MOTION        12
#define OPEN              HIGH
#define CLOSED            LOW
#define PUSH_DELAY      1000  // milliseconds to keep the button "pushed"


bool isDebugEnabled;    // enable or disable debug in this example
int stateLED;           // state to track last set value of LED
int stateNetwork;       // state of the network 



bool isPressed(int pin)
{
  return (digitalRead(pin) == CLOSED);
}

void updateRelayState()
{
  // Get the Current State of the Relay
  Serial.println("Getting Relay State...");
  if (isOn(PIN_MOTION))
  {
    Serial.println("motion detected ");
  } else {
    Serial.println("reset");
  }
}



void setup()
{
  // setup default state of global variables
  isDebugEnabled = true;

  // setup hardware pins 
  pinMode(PIN_LED, OUTPUT);     // define PIN_LED as an output
  pinMode(PIN_MOTION, INPUT);
  digitalWrite(PIN_LED, LOW);   // set value to LOW (off) to match stateLED=0
  
  if (isDebugEnabled)
  { // setup debug serial port
    Serial.begin(9600);         // setup serial with a baud rate of 9600
    Serial.println("setup..");  // print out 'setup..' on start
  }

  // Get the Current State of the Relay
  Serial.println("Getting Relay State...");
  if (isPressed(PIN_MOTION))
  {
    Serial.println("motion detected ");
  } else {
    Serial.println("reset");
  }
  
  delay(1000);
  
}

void loop()
{

  // Check the open/closed state of the relay
  updateRelayState();
  

}

