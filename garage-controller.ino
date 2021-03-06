//*****************************************************************************
#include <SoftwareSerial.h>   
#include <SmartThings.h>

#define PIN_LED           13
#define PIN_THING_RX      3
#define PIN_THING_TX      2
#define PIN_RIGHT         4
#define PIN_EXTERIOR      9
#define PIN_LEFT          7
#define PIN_INTERIOR      8
#define OPEN              HIGH
#define CLOSED            LOW
#define PUSH_DELAY      1000  // milliseconds to keep the button "pushed"

SmartThingsCallout_t messageCallout;    // call out function forward decalaration
SmartThings smartthing(PIN_THING_RX, PIN_THING_TX, messageCallout);  // constructor

bool isDebugEnabled;    // enable or disable debug in this example
int stateLED;           // state to track last set value of LED
int stateNetwork;       // state of the network 

void pushLeft()
{
  smartthing.shieldSetLED(0, 0, 2); // blue
  digitalWrite(PIN_LEFT,LOW);
  delay(PUSH_DELAY);
  digitalWrite(PIN_LEFT,HIGH);
  smartthing.shieldSetLED(0, 0, 0); // off
}

void pushRight()
{
  smartthing.shieldSetLED(0, 0, 2); // blue
  digitalWrite(PIN_RIGHT,LOW);
  smartthing.send("rightDoor pushed");
  Serial.println("rightDoor pushed");
  delay(PUSH_DELAY);
  digitalWrite(PIN_RIGHT,HIGH);
  smartthing.shieldSetLED(0, 0, 0); // off
  smartthing.send("rightDoor waiting");
  Serial.println("rightDoor waiting");
}

bool isPressed(int pin)
{
  return (digitalRead(pin) == CLOSED);
}

void updateRelayState()
{
  if (exteriorClosed != isPressed(PIN_EXTERIOR))
  {
    exteriorClosed = isPressed(PIN_EXTERIOR);
    if(exteriorClosed)
    {
      smartthing.send("exterior on");
      Serial.println("exterior on");
    } else {
      smartthing.send("exterior off");
      Serial.println("exterior off");
    }
  }
  if (interiorClosed != isPressed(PIN_INTERIOR))
  {
    interiorClosed = isPressed(PIN_INTERIOR);
    if(interiorClosed)
    {
      smartthing.send("interior pushed");
      Serial.println("interior pushed");
    } else {
      smartthing.send("interior pushed");
      Serial.println("interior pushed");
    }
  } 
}

void setNetworkStateLED()
{
  SmartThingsNetworkState_t tempState = smartthing.shieldGetLastNetworkState();
  if (tempState != stateNetwork)
  {
    switch (tempState)
    {
      case STATE_NO_NETWORK:
        if (isDebugEnabled) Serial.println("NO_NETWORK");
        smartthing.shieldSetLED(2, 0, 0); // red
        break;
      case STATE_JOINING:
        if (isDebugEnabled) Serial.println("JOINING");
        smartthing.shieldSetLED(2, 0, 0); // red
        break;
      case STATE_JOINED:
        if (isDebugEnabled) Serial.println("JOINED");
        smartthing.shieldSetLED(0, 0, 0); // off
        break;
      case STATE_JOINED_NOPARENT:
        if (isDebugEnabled) Serial.println("JOINED_NOPARENT");
        smartthing.shieldSetLED(2, 0, 2); // purple
        break;
      case STATE_LEAVING:
        if (isDebugEnabled) Serial.println("LEAVING");
        smartthing.shieldSetLED(2, 0, 0); // red
        break;
      default:
      case STATE_UNKNOWN:
        if (isDebugEnabled) Serial.println("UNKNOWN");
        smartthing.shieldSetLED(0, 2, 0); // green
        break;
    }
    stateNetwork = tempState; 
  }
}

void setup()
{
  // setup default state of global variables
  isDebugEnabled = true;
  stateLED = 0;                 // matches state of hardware pin set below
  stateNetwork = STATE_JOINED;  // set to joined to keep state off if off
  
  // setup hardware pins 
  pinMode(PIN_LED, OUTPUT);     // define PIN_LED as an output
  pinMode(PIN_RIGHT, OUTPUT);
  pinMode(PIN_LEFT, OUTPUT);
  digitalWrite(PIN_RIGHT, HIGH);
  digitalWrite(PIN_LEFT, HIGH);
  digitalWrite(PIN_LED, LOW);   // set value to LOW (off) to match stateLED=0
  
  pinMode(PIN_EXTERIOR, INPUT_PULLUP);
  pinMode(PIN_INTERIOR, INPUT_PULLUP);
  
  if (isDebugEnabled)
  { // setup debug serial port
    Serial.begin(9600);         // setup serial with a baud rate of 9600
    Serial.println("setup..");  // print out 'setup..' on start
  }

  // Get the Current State of the Doors
  Serial.println("Getting Door State...");
  if (isPressed(PIN_EXTERIOR))
  {
    exteriorClosed = true;
    smartthing.send("exterior pushed");
    Serial.println("exterior pushed");
  } else {
    exteriorClosed = false;
    smartthing.send("exterior pushed");
    Serial.println("exterior pushed");
  }
  
  delay(1000);
  
  if (isPressed(PIN_INTERIOR))
  {
    interiorClosed = true;
    smartthing.send("rightDoor closed");
    Serial.println("rightDoor closed");
  } else {
    interiorClosed = false;
    smartthing.send("rightDoor open");
    Serial.println("rightDoor open");
  }

  
  
}

void loop()
{
  // run smartthing logic
  smartthing.run();
  
  // Check the open/closed state of the doors
  //updateDoorState();
  
  // Code left here to help debut network connections
  setNetworkStateLED();
}

void messageCallout(String message)
{
  // if debug is enabled print out the received message
  if (isDebugEnabled)
  {
    Serial.print("Received message: '");
    Serial.print(message);
    Serial.println("' ");
  }

  if (message.equals("pushLeft"))
  {
    pushLeft();
  }
  else if (message.equals("pushRight"))
  {
    pushRight();
  }
    
}
