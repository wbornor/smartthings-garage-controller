//*****************************************************************************
#include <SoftwareSerial.h>   

#define PIN_MOTION        13
#define OPEN              HIGH
#define CLOSED            LOW


bool isDebugEnabled;    // enable or disable debug in this example



bool isOn(int pin)
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
  pinMode(PIN_MOTION, INPUT);
  
  if (isDebugEnabled)
  { // setup debug serial port
    Serial.begin(9600);         // setup serial with a baud rate of 9600
    Serial.println("setup..");  // print out 'setup..' on start
  }

  // Get the Current State of the Relay
  Serial.println("Getting Relay State...");
  if (isOn(PIN_MOTION))
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

