# Line Follower Robot 🤖

## 📌 Overview

The Line Follower Robot is an autonomous robotic vehicle that follows a predefined path, usually a black line on a white surface, using IR sensors. The robot continuously detects the position of the line and adjusts the speed and direction of its motors accordingly.

This project demonstrates the practical implementation of embedded systems, sensors, motor control, and Arduino programming.

## 🛠️ Components Used

- Arduino UNO
- IR Sensor Module
- L298N Motor Driver
- DC Gear Motors
- Robot Chassis
- Wheels
- Battery
- Jumper Wires

## ⚙️ Working Principle

The IR sensors continuously detect the line on the surface.

- **Line detected at the center:** Both motors move forward.
- **Line detected towards the left:** The robot adjusts its motors to turn left.
- **Line detected towards the right:** The robot adjusts its motors to turn right.
- **Line not detected:** The robot stops or performs a predefined correction.

The Arduino processes the sensor signals and sends appropriate control signals to the L298N motor driver.

## 🔌 Hardware Connections

| Component | Arduino Pin |
|---|---|
| Left IR Sensor | Digital Pin |
| Right IR Sensor | Digital Pin |
| L298N IN1 | D2 |
| L298N IN2 | D3 |
| L298N IN3 | D4 |
| L298N IN4 | D7 |
| Motor Driver Power | External Battery |

> **Note:** The motor driver should be powered using an appropriate external battery.

## 💻 Software

- Arduino IDE
- Arduino C/C++

## 🚀 Features

- Autonomous line tracking
- Real-time IR sensor detection
- Automatic left and right turning
- Motor control using L298N
- Low-cost and simple design
- Arduino-based embedded system

## 📂 Project Structure

```text
Line-Follower-Robot/
│
├── line_follower.ino
├── README.md
└── images/
    └── robot.jpg
