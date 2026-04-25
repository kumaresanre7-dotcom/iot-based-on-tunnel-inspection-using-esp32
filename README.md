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
The rover system is divided into two main modules:

1. Rover Controller (ESP32)
Handles:

Motor control
Sensor data acquisition
Blynk communication
Obstacle detection
Gas monitoring
2. Camera Controller (ESP32-CAM)
Handles:

Camera initialization
Video streaming server
Sending camera stream link to the main ESP32

## Project Folder Structure
IoT-Based-Tunnel-Inspection-Rover-using-ESP32

repo/
├── README.md/           ← Professional readme with all 4 photos + hardware table

├── index.html   ← Visual project showcase (works as GitHub Pages website) 

├── esp32 camera.ino

├── firmware/
│   └── project_main.ino     ← Full working ESP32 firmware with Blynk + all sensors

└── images/
    ├── rover_top.jpg
    ├── rover_front.jpg
    ├── rover_side1.jpg
    └── rover_side2.jpg

## Working Principle

1. The **ESP32 connects to WiFi** and communicates with the **Blynk IoT platform**.
2. Sensor data (gas levels, temperature, humidity, and distance) is continuously monitored.
3. If dangerous conditions are detected, alerts are sent to the **Blynk mobile application**.
4. The **ESP32-CAM streams live video** from the rover.
5. The rover can be controlled remotely through in **Blynk virtual buttons**.

## How to Run
1. Clone this repo
2. Open `firmware/rover_main.ino` in Arduino IDE
3. Install required libraries via Library Manager
4. Add your WiFi credentials and Blynk Auth Token in `config.h`
5. Flash to ESP32 board
6. Open Blynk app and connect

## Author
R E Kumaresan — [LinkedIn] https://www.linkedin.com/in/r-e-kumaresan-9a4a59264| kumaresanre7@gmail.com
