🚁 DroneSwarmSimulation
A multi-drone autonomous swarm simulation with physics, encrypted networking, telemetry logging, and a Java Swing visualizer.
📌 Overview

DroneSwarmSimulation is a full 2D multi-agent swarm simulation developed in C++ with real-time visualization provided by a Java Swing application.
The system models autonomous drones navigating a physical world using Newtonian mechanics, formation control algorithms, and a simulated lossy communication network.

This repo demonstrates:

Applied physics simulation

Multi-agent control (formation flight)

Realistic communication constraints (latency, jitter, packet drops, XOR encryption)

Clean object-oriented architecture

Cross-language visualization (C++ → CSV → Java Swing)

Modular code with full Doxygen documentation

This project was built from scratch to showcase engineering ability, system design, and simulation frameworks.

🚀 Features
🧠 Swarm Control

N-drone formation flight using PD controllers

Per-drone target offsets and goal acquisition

Automatic thrust control and velocity damping

⚙️ Physics Engine

Newtonian integration (semi-implicit Euler)

Gravity, boundary collision, and speed limits

Clean vector math abstraction (Vector2)

Drone mass, thrust, and envelope limits

🔐 Networking Layer

Simulated realistic radio communication:

Base latency + random jitter

Configurable packet drop probability

XOR payload encryption

Delivery timestamps, message IDs

Per-node inbox messages

Output logged to comms_log.csv

📊 Telemetry Logging

Every timestep, the simulator logs:

time, droneId, x, y, vx, vy


Into simulation_log.csv, which the Java visualizer reads.

🎨 Java Swing Visualizer

Reads CSV logs directly

Renders drones as moving colored circles

Displays time, drone IDs, and frame count

Scales world coordinates into viewport

Smooth ~30 FPS animation

📂 Repository Structure
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
