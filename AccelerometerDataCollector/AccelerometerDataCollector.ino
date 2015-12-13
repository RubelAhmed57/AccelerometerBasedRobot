#include <SoftwareSerial.h>

int led = 13;

SoftwareSerial bt(10, 11); //rx tx

float values = 0;

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
    delay(10);
  }

  if (values > -7) digitalWrite(led, HIGH);
  else digitalWrite(led, LOW);
}
