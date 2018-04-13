#include<Arduino.h>

const int trigPin = 8;
const int echoPin = 9;

const int motorA_direction = 13;
const int motorA_pwm = 11;

const int motorB_direction = 12;
const int motorB_pwm = 10; 

long duration;
int distance;

void setup() {
  // Sets Port 8,10,11 for output, 9,12,13 as Input
  // Port 8 is being used as a trigger
  // Port 9 is being used for echo
  DDRB = B00111101;
  Serial.begin(9600);
}

void loop() {
  int distance = getDistance();
  moveForward(distance);
  if(distance < 10)
  {
    rotate();
  }
}

int getDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);

  return distance;
}

void moveForward(int distance)
{
  int speed = map(distance, 0, 4000, 200, 255);
  Serial.print("Moving Forward with speed: ");
  Serial.println(speed);
  digitalWrite(motorA_direction, HIGH);
  digitalWrite(motorB_direction, HIGH);
  analogWrite(motorA_pwm, speed);
  analogWrite(motorB_pwm, speed);
}

void rotate()
{
  Serial.println("Rotating");
  digitalWrite(motorA_direction, LOW);
  digitalWrite(motorB_direction,HIGH);
  analogWrite(motorA_pwm, 255);
  analogWrite(motorB_pwm, 255);
  delay(500);
  digitalWrite(motorA_direction, HIGH);
  digitalWrite(motorB_direction, HIGH);
  digitalWrite(motorA_pwm, LOW);
  digitalWrite(motorB_pwm, LOW);
  Serial.println("Done Rotating");
}
