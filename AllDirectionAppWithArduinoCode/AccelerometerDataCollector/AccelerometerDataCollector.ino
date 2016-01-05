#include <SoftwareSerial.h>
#include <Motor.h>

motorpins pins = {2, 3, 4, 5};

Motor motor(pins);

int led = 13;

SoftwareSerial bt(10, 11); //rx tx

float values = -100;
float yValues = -100;

int x_value = 0;
int y_value = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bt.begin(9600);
  pinMode(led, OUTPUT);
}

int getX(String value){
  String x = value.substring(1, value.indexOf(','));
  return x.toInt();
}

int getY(String value){
  String y = value.substring(value.indexOf(',') + 1, value.indexOf(')'));
  return y.toInt();
}



void loop() {
  // put your main code here, to run repeatedly:
  if (bt.available() > 0){
    //values = bt.parseFloat();
    //yValues = bt.parseFloat();
    
    //Serial.println("x values: " + String(values) + "\n y values: " + String(yValues));
    String compositeData = bt.readStringUntil('\n');
    x_value = getX(compositeData);
    y_value = getY(compositeData);

    Serial.println("x: " +  String(x_value));
//    Serial.println(x);
    
    delay(10);
  }

  if (x_value > -8 && x_value < -3){
    Serial.println("FORWARD");
    motor.go(255, 255, FORWARD);
  }

  else if (x_value > 3 && x_value < 8){
    Serial.println("BACKWARD");
    motor.go(255, 255, BACKWARD);
  }

  else if (y_value > -8 && y_value < -3){
    Serial.println("LEFT");
    motor.go(0, 255, LEFT);
  }

  else if (y_value > 3 && y_value < 8){
    Serial.println("RIGHT");
    motor.go(255, 0, RIGHT);
  }

  else {
    motor.go(0, 0, NOWHERE);
  }

//  if (x_value > -10 && x_value < -3) {
//    
//  }
//  else if (x_value > 3 && x_value < 10) {
//        Serial.println("BACKWARD");
//    motor.go(255, 255, BACKWARD);
//  }
//  else if (y_value > -10 && y_value < -3){
//        Serial.println("LEFT");
//    motor.go(255, 0, LEFT);
//  }
//  else if (y_value > 3 && y_value < 10){
//        Serial.println("RIGHT");
//    motor.go(0, 255, RIGHT);
//  }
//  else {
//        Serial.println("STOP");
//    motor.go(0, 0, NOWHERE);
//  }
  
  //if (values > -7) {digitalWrite(led, HIGH); motor.go(255, 255, FORWARD); }
  //else { digitalWrite(led, LOW); motor.go(0, 0, NOWHERE); }
}
