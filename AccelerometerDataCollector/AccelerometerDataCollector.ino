#include <SoftwareSerial.h>
#include <Motor.h>

motorpins pins = {2, 3,4,5};

Motor motor(pins);

int led = 13;

SoftwareSerial bt(51, 52); //rx tx

float values = -100;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bt.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (bt.available() > 0){
    values = bt.parseFloat();
    Serial.println(values);
    delay(10);
  }

  if (values > -7) {digitalWrite(led, HIGH); motor.go(100, 100, FORWARD); }
  else { digitalWrite(led, LOW); motor.go(0, 0, NOWHERE); }
}
