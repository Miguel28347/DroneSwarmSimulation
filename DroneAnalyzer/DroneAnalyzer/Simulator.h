#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include "Drone.h"
#include "World.h"
#include "Network.h"

/*
 * @class: 
 *         Simulator
 * @brief:
 *         Central engine that coordinates drones, physics, and communication.
 *
 * The Simulator manages all active drones, updates them each time-step, applies
 * thrust commands, tracks simulation time, and sends periodic status reports
 * over the communication network. It acts as the high-level orchestrator for
 * the physics environment, world settings, and swarm-level behaviors.
 *
 * Responsibilities:
 * - Create drones and initialize their parameters.
 * - Apply thrust vectors to individual drones.
 * - Step the physics simulation forward by a fixed or variable dt.
 * - Relay drone telemetry through the Network subsystem.
 * - Maintain global simulation time and reporting intervals.
 *
 * This class is intended to be used by a main program or higher-level scenario
 * engine that issues commands and reads telemetry.
 */

class Simulator {
public:

    /*
     * @brief: 
     *         Constructs a new Simulator using the provided world settings.
     * @param:
     *         world Global environment settings (gravity, bounds, etc.).
     */

    Simulator(const World& world);

    /*
     * @brief:
     *         Adds a new drone to the simulation.
     *
     * @param: parameters
     *         Initial configuration values (mass, thrust limits, etc.).
     * @param: startPos
     *         Starting position of the drone in world coordinates.
     * @return: The unique ID assigned to the new drone.
     */

    int addDrone(const DroneParams& parameters, const Vector2& startPos);

    /*
     * @brief: 
     *         Sets the direction of the drone's thrust vector.
     *
     * This does not set the magnitude—only the normalized direction in which
     * thrust is applied. Magnitude can be set separately via setDroneThrustForce().
     *
     * @param: droneId
     *         ID of the drone to command.
     * @param: direction
     *         The thrust direction vector.
     */

    void setDroneThrustDirection(int droneId, const Vector2& direction);

    /*
     * @brief:
     *         Sets the full thrust force vector applied to a drone.
     *
     * This directly sets both direction and magnitude of the thrust. Used for
     * more precise control (e.g., autopilot or AI controller).
     *
     * @param: droneId
     *         ID of the drone to command.
     * @param: force
     *         The thrust force vector.
     */

    void setDroneThrustForce(int droneId, const Vector2& force);

    /*
     * @brief: 
     *         Clears any applied thrust on the given drone.
     *
     * Effectively sets the thrust vector to zero, meaning the drone will only be
     * influenced by gravity and other external forces.
     *
     * @param: droneId
     *         ID of the drone to modify.
     */

    void clearDroneThrust(int droneId);

    /*
     * @brief:
     *         Advances the entire simulation forward by the given timestep.
     *
     * This method:
     * - Updates all drone physics.
     * - Applies thrust and external forces.
     * - Increments simulation time.
     * - Sends periodic telemetry via the Network subsystem.
     *
     * @param: dt
     *         Time step in seconds.
     */

    void step(double dt);

    /*
     * @brief: Returns a read-only reference to all drones.
     *
     * Useful for inspection or rendering systems that need the current state
     * of the swarm.
     *
     * @return:
     *          const reference to internal drone list.
     */

    const std::vector<Drone>& getDrones() const { return mDrones; }

    /*
     * @brief:
     *         Prints a summary of all communication messages exchanged
     *         during the simulation.
     *
     * Intended to be called by main() after the simulation completes.
     */

    void printCommsSummary() const;

private:
    
    /*
     * @brief:
     *         Sends a single drone's status message over the communication network.
     *
     * Called internally at each reporting interval.
     *
     * @param: d 
     *         The drone whose status is being reported.
     * @param:
     *         currentTime  Simulation time at which the report is generated.
     */

    void sendDroneStatus(const Drone& d, double currentTime);

    // World settings
    World mWorld;

    // Collection of all active drones in the simulation
    std::vector<Drone> mDrones;

    // Comms network + timing
    Network mComms;
    double mSimTime;
    double mNextReportTime;
    double mReportInterval;
};

#endif // SIMULATOR_H
