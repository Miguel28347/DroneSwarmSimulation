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

🧩 Architecture Diagram (Text-Based)
+-----------------------+
|      Simulator        |
|-----------------------|
| - manages drones      |
| - runs physics        |
| - steps network       |
+-----------+-----------+
            |          
            v
+-----------------------+       +---------------------+
|        Drone          |<----->|      Network        |
|-----------------------|       |---------------------|
| position, velocity    |       | latency, jitter     |
| thrust, params        |       | packet dropping     |
| physics update        |       | XOR encryption      |
+-----------+-----------+       +----------+----------+
            |                                |
            | telemetry                      | logs comms
            v                                v
      simulation_log.csv             comms_log.csv
            |
            v
+----------------------------+
|   Java Swing Visualizer    |
|----------------------------|
| animates drone trajectories|
+----------------------------+

🔧 Building & Running
1️⃣ Build & Run the C++ Simulator

Use Visual Studio, g++, or any C++17 compiler.

Example (g++):

g++ -std=c++17 main.cpp Simulator.cpp Drone.cpp -o DroneSim
./DroneSim


Output files:

simulation_log.csv

comms_log.csv

2️⃣ Run the Java Visualizer

Open /java-visualizer/DroneVisualizerSwing.java and modify:

final String csvPath = "path/to/simulation_log.csv";


Then run with:

javac DroneVisualizerSwing.java
java DroneVisualizerSwing


You will see a real-time animation of the swarm.

📝 Example Output

(You can add screenshots later)

t=1.50
Drone 0 pos=(54.2, 57.8) vel=(1.2, 0.9)
Drone 1 pos=(66.3, 57.9) vel=(-1.1, 0.8)
Drone 2 pos=(60.0, 64.1) vel=(0.0, -1.5)
Drone 3 pos=(60.1, 52.3) vel=(-0.2, 1.4)


Visualizer GUI example:
(Add when ready)

🎯 Purpose

This project demonstrates:

Ability to architect and implement a multi-module codebase

Realistic simulation of physics + networking

Cross-language integration (C++ + Java)

Engineering design for autonomous systems

Professional documentation for academic/industry review

📘 Future Enhancements

Formation switching and dynamic target tracking

Collision avoidance & obstacle simulation

Sensor noise + estimator (EKF filter)

Web-based visualization via WebGL

Real-time UDP networking to ROS
