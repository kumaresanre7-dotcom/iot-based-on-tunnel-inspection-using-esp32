# IoT-Based Tunnel Inspection Rover using ESP32

An ESP32-powered robotic rover for remote inspection of hazardous tunnel 
environments with real-time video streaming, gas detection, and live 
monitoring via Blynk IoT dashboard.

## Features
- Live video streaming via ESP32-CAM
- Real-time gas, temperature & ultrasonic sensor monitoring
- PWM-based motor control using L298N driver
- Remote control and alerts via Blynk IoT dashboard
- Automated hazard alerts

## Hardware Used
| Component | Purpose |
|---|---|
| ESP32 (main controller) | Central processing & WiFi |
| ESP32-CAM | Live video stream |
| MQ-2 Gas Sensor | Gas / smoke detection |
| DHT11 Temperature Sensor | Ambient temperature |
| HC-SR04 Ultrasonic Sensor | Obstacle detection |
| L298N Motor Driver | PWM motor control |
| DC Gear Motors (x2) | Rover locomotion |

## Communication Protocols Used
UART (ESP32-CAM serial), I2C (sensor bus), PWM (motor control)

## Software & Tools
- Arduino IDE
- Embedded C / C++
- Blynk IoT Platform
- Libraries: BlynkSimpleEsp32, ESP32CAM

## System Architecture
[Add your block diagram image here]

## How to Run
1. Clone this repo
2. Open `firmware/rover_main.ino` in Arduino IDE
3. Install required libraries via Library Manager
4. Add your WiFi credentials and Blynk Auth Token in `config.h`
5. Flash to ESP32 board
6. Open Blynk app and connect

## Author
R E Kumaresan — [LinkedIn](your-linkedin-url) | kumaresanre7@gmail.com
