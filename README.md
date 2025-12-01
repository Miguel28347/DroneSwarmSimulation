# 🚁 DroneSwarmSimulation

This is a multi-drone autonomous swarm simulator deaturing physics, encrypted networking, telemetry logging, and a Java Swing visualizer. 
# 📌 Overview

DroneSwarmSilumation is a full 2D multi-drone swarm enviornment built in C++, with real-time visualization provided through a Java Swing application. It models autonomous drones navigating a simulated world using:

- Newtonian Physics
- Formation control with proportional-derivative controllers
- A lossy, encrypted communication network
- Real-time telemetry exported for visualization

# 🚀 Features

## 🧠 Swarm Control

- N-drone formation flight using proportional-derivative (PD) controllers
- Per-drone goal offsets and dynamic target acquistion
- Automatic thrust control and velocity damping

## ⚙️ Physics Engine

- Semi-implicit Euler integration
- Gravity, boundary collision handling, and speed limiting
- Clean vector math abstraction(Vector2)
- Drone mass, thrust and envelope parameters

## 🔐 Networking Layer  
Realistic radio-style network model with:

- Base latency + random jitter
- Configurable packet-drop probablity
- XOR payload encryption(lightweight)
- Message IDs and timestamps
- per-node inbox messages queues
- Communication logs saved to comms_log.csv

## 📊 Telemetry Logging  
Every simulation step logs:  

time, droneId, x, y, vx, vy  

Saved to simulation_log.csv, which the Java visualizer reads.

## 🎨 Java Swing Visualizer

- Reads CSV logs in real-time
- Displays drones as animated colored circles
- Scales world coordinates dynamically
- Shows time, drone IDs, and frame count
- ~30 FPS animation

## 📂 Repository Structure
DroneSwarmSimulation/
│
├── Drone.cpp
├── Drone.h
├── Network.h
├── Message.h
├── Simulator.cpp
├── Simulator.h
├── Vector2.h
├── World.h
├── Node.h
├── main.cpp
│
├── Java-Visualizer/
│   └── DroneVisualizerSwing.java
│
├── .gitignore
└── README.md

## 🧩 Architecture Diagram (Text-Based)

SECTION UNDER CONSTRUCTION

## 🔧 Building & Running  
1️⃣ Build & Run the C++ Simulator  

Use Visual Studio, g++, or any C++17 compiler.

Example (Visual Studios):  
- Open Visual Studios
- Open project folder
- Compile project  

2️⃣ Run the Java Visualizer  

- Open your Java IDE 
- Then find DroneVisualizerSwing.java
- Compile/ run the project

## 📝 Example Output

C++ compile output: 
<img width="1473" height="749" alt="Screenshot 2025-12-01 021316" src="https://github.com/user-attachments/assets/36fd8bac-bf2e-45b7-97c1-8a43a3da92aa" />


Visualizer GUI example:

https://github.com/user-attachments/assets/aaa0557c-795c-4097-812c-72f0ff004e88

## 🎯 Purpose

This project demonstrates:

Ability to architect and implement a multi-module codebase

Realistic simulation of physics + networking

Cross-language integration (C++ + Java)

Engineering design for autonomous systems

Professional documentation for academic/industry review

## 📘 Future Enhancements

Formation switching and dynamic target tracking

Collision avoidance & obstacle simulation

Sensor noise + estimator (EKF filter)

Web-based visualization via WebGL

Real-time UDP networking to ROS
