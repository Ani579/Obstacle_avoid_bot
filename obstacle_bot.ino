#include <Servo.h>

Servo sonarServo;

// ---------- Ultrasonic ----------
#define TRIG_PIN 10
#define ECHO_PIN 11

// ---------- Servo ----------
#define SERVO_PIN 12

// ---------- L298N ----------
#define ENA 5
#define IN1 2
#define IN2 3

#define ENB 6
#define IN3 4
#define IN4 7

// ---------- Settings ----------
#define OBSTACLE_DISTANCE 20
#define MOTOR_SPEED 180

// Servo angles
#define CENTER 90
#define LEFT 150
#define RIGHT 30


// Measure distance using HC-SR04
long getDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    return 400;   // No echo = assume clear
  }

  long distance = duration * 0.034 / 2;

  return distance;
}


// ---------- Motor Functions ----------

void moveForward() {

  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


void moveBackward() {

  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


void turnLeft() {

  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);

  // Left motors backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // Right motors forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


void turnRight() {

  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);

  // Left motors forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Right motors backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


void stopRobot() {

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


// ---------- Setup ----------

void setup() {

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  sonarServo.attach(SERVO_PIN);

  sonarServo.write(CENTER);

  Serial.begin(9600);

  delay(1000);
}


// ---------- Main Loop ----------

void loop() {

  sonarServo.write(CENTER);
  delay(200);

  long frontDistance = getDistance();

  Serial.print("Front: ");
  Serial.print(frontDistance);
  Serial.println(" cm");


  // Path is clear
  if (frontDistance > OBSTACLE_DISTANCE) {

    moveForward();
  }

  // Obstacle detected
  else {

    stopRobot();
    delay(200);

    // Move sensor to LEFT
    sonarServo.write(LEFT);
    delay(500);

    long leftDistance = getDistance();

    Serial.print("Left: ");
    Serial.print(leftDistance);
    Serial.println(" cm");


    // Move sensor to RIGHT
    sonarServo.write(RIGHT);
    delay(500);

    long rightDistance = getDistance();

    Serial.print("Right: ");
    Serial.print(rightDistance);
    Serial.println(" cm");


    // Return sensor to center
    sonarServo.write(CENTER);
    delay(200);


    // Choose direction
    if (leftDistance > rightDistance) {

      Serial.println("Turning LEFT");

      turnLeft();
      delay(500);

    } 
    else {

      Serial.println("Turning RIGHT");

      turnRight();
      delay(500);
    }

    stopRobot();
    delay(100);
  }
}