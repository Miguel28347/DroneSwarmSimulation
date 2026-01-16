# 🚁 DroneSwarmSimulation

This is a multi-drone semi-autonomous swarm simulator featuring physics, encrypted networking, telemetry logging, and a Java Swing visualizer. 
# 📌 Overview

DroneSwarmSimulation is a full 2D multi-drone swarm environment built in C++, with real-time visualization provided through a Java Swing application. It models autonomous drones navigating a simulated world using:

- Newtonian Physics
- Formation control with proportional-derivative controllers
- A lossy, encrypted communication network
- Real-time telemetry exported for visualization

# 🚀 Features

## 🧠 Swarm Control

- N-drone formation flight using proportional-derivative (PD) controllers
- Per-drone goal offsets and dynamic target acquisition
- Automatic thrust control and velocity damping

## ⚙️ Physics Engine

- Semi-implicit Euler integration
- Gravity, boundary collision handling, and speed limiting
- Clean vector math abstraction (Vector2)
- Drone mass, thrust and envelope parameters

## 🔐 Networking Layer  
Realistic radio-style network model with:

- Base latency + random jitter
- Configurable packet-drop probability
- XOR payload encryption (lightweight)
- Message IDs and timestamps
- Per-node inbox message queues
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
│&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└── DroneVisualizerSwing.java  
│  
├── .gitignore  
└── README.md  

## 🔧 Building & Running  
1️⃣ Build & Run the C++ Simulator  

Any C++17 compiler works (Visual Studio recommended)

Visual Studio Example:  
- Open the project folder
- Build -> Run 

📝 C++ Example Output

C++ compile output: 
<img width="1473" height="749" alt="Screenshot 2025-12-01 021316" src="https://github.com/user-attachments/assets/36fd8bac-bf2e-45b7-97c1-8a43a3da92aa" />  

2️⃣ Run the Java Visualizer  

- Open in IntelliJ/ NetBeans/ VS Code  
- Compile and run DroneVisualizerSwing.java  

📝 Java Example Output


https://github.com/user-attachments/assets/aaa0557c-795c-4097-812c-72f0ff004e88

## 🎯 Technical Summary


- Autonomous formation-control swarm simulation
- Newtonian motion modeling
- Simulated distributed networking with packet loss
- Event Dispatch Thread (EDT) visualization
- Cross-language integration (C++ → Java)
- Modular, scalable system architecture

## 📘 Future Enhancements  
- Dynamic formation switching based on mission objectives
- Collision avoidance with obstacle detection and path replanning
- Autonomous target selection and task allocation
- Real-time UDP networking to ROS/PX4 for hardware-in-the-loop testing
- Decentralized decision-making with consensus algorithms
- 3D physics simulation with aerodynamic modeling
