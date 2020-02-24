#include <Servo.h>


#define LED_G1 2
#define LED_Y1 3
#define LED_R1 4
#define LED_G2 5
#define LED_Y2 6
#define LED_R2 7
#define LED_G3 8
#define LED_Y3 9
#define LED_R3 10
#define TRIG 11
#define ECHO 12
#define SERVO_PIN 13



bool isTurned; //boolean to see if servo is turned. false right , true is front
int pinCount = 9;
long duration;
int distance;
Servo servo1;

int ledPins[] = {
  LED_G1, LED_Y1, LED_R1, LED_G2, LED_Y2, LED_R2, LED_G3, LED_Y3, LED_R3, SERVO_PIN
};

void setup() {
  // put your setup code here, to run once:
  //initialise every pin in this array
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(ledPins[thisPin], OUTPUT);
    digitalWrite(ledPins[thisPin], LOW);

  }

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(LED_G2, HIGH);
  digitalWrite(LED_R1, HIGH);
  digitalWrite(LED_R3, HIGH);

  servo1.attach(SERVO_PIN);
  servo1.write(10);
  isTurned = false;
  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print(F("distance in cm: "));
  Serial.println(distance);

  
  if ((distance < 14) && (!isTurned)) {
    servo1.write(70);
    isTurned = true;
    changeLights();
  }
  else if ((distance < 10) && (isTurned)) {
    servo1.write(10);
    isTurned = false;
    changeLights();
  }


  delay(130);
}

void changeLights()
{
  Serial.println(F("BEGIN CHANGE_LIGHTS FUN"));
  digitalWrite(LED_R1, HIGH);
  digitalWrite(LED_R3, HIGH);
  digitalWrite(LED_G2, HIGH);
  delay(8000);//how long green(only change this)
  digitalWrite(LED_G2, LOW);
  digitalWrite(LED_Y2, HIGH);
  delay(3000);
  digitalWrite(LED_Y2, LOW);
  digitalWrite(LED_R2, HIGH);
  delay(700);
  digitalWrite(LED_R3, LOW);
  digitalWrite(LED_R1, LOW);
  digitalWrite(LED_G1, HIGH);
  digitalWrite(LED_G3, HIGH);
  delay(8000);//how long green (only change this)
  digitalWrite(LED_G1, LOW);
  digitalWrite(LED_G3, LOW);
  digitalWrite(LED_Y1, HIGH);
  digitalWrite(LED_Y3, HIGH);
  delay(3000);
  digitalWrite(LED_Y1, LOW);
  digitalWrite(LED_Y3, LOW);
  digitalWrite(LED_R1, HIGH);
  digitalWrite(LED_R3, HIGH);
  delay(700);
  digitalWrite(LED_R2, LOW);
  digitalWrite(LED_G2, HIGH);



}
