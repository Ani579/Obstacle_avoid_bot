# Arduino Obstacle Avoiding Robot

An autonomous obstacle avoiding robot developed using an Arduino UNO, L298N motor driver, four BO geared motors, an HC-SR04 ultrasonic sensor, and a servo motor. The robot is designed to detect obstacles in its path and automatically change its direction without requiring manual control.

The HC-SR04 ultrasonic sensor is mounted on a servo motor, which allows the sensor to scan different directions when an obstacle is detected. The Arduino UNO processes the distance measurements and controls the motors through the L298N motor driver. Based on the available space around the robot, it automatically decides whether to turn left or right and continues moving forward.

This project demonstrates the practical implementation of microcontrollers, ultrasonic sensing, servo control, motor driving, PWM-based speed control, and autonomous navigation using an embedded system.

---
## How to get the code:

Use the file uploaded named obstacle_bot.ino to get the code for your arduino uno.

## Project Overview

The primary objective of this project is to develop a simple, low-cost autonomous robotic vehicle capable of navigating an environment while avoiding obstacles.

The Arduino UNO acts as the central controller of the system. It continuously receives distance information from the HC-SR04 ultrasonic sensor. When the path ahead is clear, the robot moves forward. When an obstacle is detected within the predefined distance, the robot stops and uses the servo-mounted ultrasonic sensor to examine the surrounding area. The Arduino then determines a suitable direction for the robot to turn before continuing its movement.

The project is suitable for understanding the fundamentals of Arduino programming, embedded systems, robotics, ultrasonic sensors, motor control, servo motors, and autonomous navigation.

---

## Equipment and Components Used

The robot is constructed using an Arduino UNO as the main microcontroller, an L298N dual H-bridge motor driver for controlling the DC motors, four BO geared DC motors for movement, an HC-SR04 ultrasonic sensor for obstacle detection, and a servo motor for rotating the ultrasonic sensor.

A suitable external battery or power source is used for the motors and motor driver. The mechanical structure consists of a robot chassis and four wheels. Jumper wires and other basic electronic components are used to establish the required electrical connections.

| Component | Quantity | Purpose |
|---|---:|---|
| Arduino UNO | 1 | Main microcontroller |
| L298N Motor Driver | 1 | Controls the DC motors |
| BO Gear Motors | 4 | Provides movement |
| HC-SR04 Ultrasonic Sensor | 1 | Detects obstacles and measures distance |
| Servo Motor | 1 | Rotates the ultrasonic sensor |
| Robot Chassis | 1 | Provides the mechanical structure |
| Wheels | 4 | Enables robot movement |
| Battery / Power Source | 1 | Powers the system |
| Jumper Wires | As required | Electrical connections |

---

## Pin Configuration

The following pin configuration is used in the current implementation.

### HC-SR04 Ultrasonic Sensor

| HC-SR04 Pin | Arduino UNO Pin |
|---|---|
| VCC | 5V |
| GND | GND |
| TRIG | D10 |
| ECHO | D11 |

### Servo Motor

| Servo Pin | Arduino UNO Pin |
|---|---|
| Signal | D12 |
| VCC | 5V |
| GND | GND |

### L298N Motor Driver

| L298N Pin | Arduino UNO Pin |
|---|---|
| ENA | D5 |
| IN1 | D2 |
| IN2 | D3 |
| IN3 | D4 |
| IN4 | D7 |
| ENB | D6 |

The two motors on the left side are connected to one output channel of the L298N, while the two motors on the right side are connected to the other output channel. This allows the Arduino to control the left and right sides of the robot independently.

---

## Working Principle

The robot works by using ultrasonic sensing to detect objects in its surroundings. The HC-SR04 ultrasonic sensor emits a high-frequency sound pulse through its trigger pin and receives the reflected signal through its echo pin. The Arduino measures the time taken for the ultrasonic wave to return and calculates the approximate distance between the sensor and the obstacle.

During normal operation, the ultrasonic sensor faces forward and continuously checks the path of the robot. If the measured distance is greater than the predefined obstacle threshold, the robot continues moving forward. When an obstacle is detected within the threshold distance, the Arduino stops the motors and rotates the servo motor to change the direction of the ultrasonic sensor. The sensor measures the available distance on different sides, and the Arduino uses these measurements to determine a suitable direction for the robot to turn. After turning, the robot continues moving forward and repeats the sensing process.

This continuous sensing and movement cycle enables the robot to navigate autonomously while avoiding obstacles.

---

## Software and Programming

The robot is programmed using Arduino C++ and developed using the Arduino IDE.

The `Servo.h` library is used to control the servo motor that rotates the ultrasonic sensor. The Arduino also uses PWM signals through the ENA and ENB pins of the L298N motor driver to control the speed of the motors.

The current program uses an obstacle detection threshold of approximately 20 cm and a motor speed value of 180 PWM. These values can be modified according to the robot's hardware and operating environment.

```cpp
#define OBSTACLE_DISTANCE 20
#define MOTOR_SPEED 180