#include <Servo.h>

Servo lidServo;

// Pin Definitions
const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 6;

// Variables
long duration;
int distance;

// Distance at which lid opens
const int openDistance = 20;   // in centimeters

void setup()
{
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lidServo.attach(servoPin);

  // Keep lid closed at startup
  lidServo.write(0);
}

void loop()
{
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  // Read echo time
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance (cm)
  distance = duration * 0.0343 / 2;

  // Print distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If hand is close, open lid
  if (distance > 0 && distance <= openDistance)
  {
    lidServo.write(90);      // Open lid
    delay(5000);             // Wait 5 seconds
    lidServo.write(0);       // Close lid
    delay(500);
  }

  delay(100);
}
