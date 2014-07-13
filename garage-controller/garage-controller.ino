//*****************************************************************************
#include <SoftwareSerial.h>   

#define PIN_LED           13
#define PIN_MOTION        A0
#define OPEN              HIGH
#define CLOSED            LOW


bool isDebugEnabled;    // enable or disable debug in this example



bool isOpen(int pin)
{
  return (digitalRead(pin) == OPEN);
}

void updateRelayState()
{
  // Get the Current State of the Relay
  Serial.println("Getting Relay State...");
  if (isOpen(PIN_MOTION))
  {
    Serial.println("motion detected");
    digitalWrite(PIN_LED, HIGH);   // set value to HIGH (on)
  } else {
    Serial.println("nothing");
    digitalWrite(PIN_LED, LOW);   // set value to LOW (off)
  }
}



void setup()
{
  // setup default state of global variables
  isDebugEnabled = true;

  // setup hardware pins 
  pinMode(PIN_MOTION, INPUT);
  pinMode(PIN_LED, OUTPUT);     // define PIN_LED as an output
  
  if (isDebugEnabled)
  { // setup debug serial port
    Serial.begin(9600);         // setup serial with a baud rate of 9600
    Serial.println("setup..");  // print out 'setup..' on start
  }

  // Get the Current State of the Relay
  Serial.println("Getting Relay State...");
  if (isOpen(PIN_MOTION))
  {
    Serial.println("motion detected ");
    digitalWrite(PIN_LED, HIGH);   // set value to HIGH (on)
  } else {
    Serial.println("noothing");
    digitalWrite(PIN_LED, LOW);   // set value to LOW (off)
  }
  
  delay(1000);
  
}

void loop()
{

  // Check the open/closed state of the relay
  updateRelayState();
  
  delay(1000);
}

