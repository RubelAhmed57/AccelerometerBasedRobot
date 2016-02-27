#include <SoftwareSerial.h>
#include <Motor.h>
#include <Servo.h>

#define KICK_ANGLE 90
#define NO_KICK_ANGLE 5
#define FLIPPER_PIN 7

#define RX 10
#define TX 11
#define spd 200
#define baud 9600

String incomingString = "";

SoftwareSerial bluetooth(RX, TX);

enum ControlMode {ACCELEROMETER, BUTTON};
ControlMode controlMode;

//Motor pin configs
//motorPins pins = {6, 9, 3, 5};

motorPins pins = {3, 5, 6, 9};

Motor motor(pins);

//values
float values =  -100;
float yValues = -100;

int x_value = 0;
int y_value = 0;

int direction = 0;

int getX (String value){
  String x = value.substring(1, value.indexOf(','));
  return x.toInt();
}

int getY(String value){
  String y = value.substring(value.indexOf(',') + 1 , value.indexOf(')'));
  return y.toInt();
}

bool isKicked = false;


Servo flipper;

void setup() {
  Serial.begin(baud);
  bluetooth.begin(baud);
  controlMode = ACCELEROMETER; //Default Control Mode
  flipper.attach(FLIPPER_PIN);
  
}

void loop() {
  if (bluetooth.available() > 0){
    String compositeData = bluetooth.readStringUntil('\n');
    incomingString = compositeData;
    if (compositeData.startsWith("~")) controlMode = BUTTON;
    else {
      controlMode = ACCELEROMETER;
      x_value = getX(compositeData);
      y_value = getY(compositeData);
    }
    delayMicroseconds(10);
  }

  if (controlMode == ACCELEROMETER){
    if (x_value > -8 && x_value < -3) motor.go(spd, spd, FORWARD);
    else if (x_value > 3 && x_value < 8) motor.go(spd, spd, BACKWARD);
    else if (y_value > 3 && y_value < 8) motor.go(spd, spd, ANTICLOCKWISE);
    else if (y_value > -8 && y_value < -3) motor.go(spd, spd, CLOCKWISE);
    else motor.go(0, 0, NOWHERE);
  } else {
    if (incomingString.equals("~FORWARD")) motor.go(spd, spd, FORWARD);
    else if (incomingString.equals("~BACKWARD")) motor.go(spd, spd, BACKWARD);
    else if (incomingString.equals("~LEFT")) motor.go(spd, spd, ANTICLOCKWISE);
    else if (incomingString.equals("~RIGHT")) motor.go(spd, spd, CLOCKWISE);
    else if (incomingString.equals("~KICK")) { 
      if (isKicked == false){
        flipper.write(KICK_ANGLE); 
        isKicked = true;
      }
    }
    else {
      motor.go(0, 0, NOWHERE);
      if (isKicked = true) {
        flipper.write(NO_KICK_ANGLE);
        isKicked = false;
      }
    }
  }

}
