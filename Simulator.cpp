#include "Simulator.h"
#include <sstream>
#include <iomanip>

/*
 * @brief: Constructs a Simulator using the provided world and initializes
 *        communication network parameters.
 *
 * Initializes:
 * - The global world configuration (gravity, boundaries).
 * - A communication network with base latency, jitter, and drop probability.
 * - Simulation timing values (current time, reporting intervals).
 *
 * Also registers the "HQ" node in the network, which receives all drone reports.
 *
 * @param: world
 *         Reference to the global world settings.
 */

Simulator::Simulator(const World& world)
    : mWorld(world),
    mComms(/*baseLatency=*/0.5,
        /*jitter=*/0.2,
        /*dropProbability=*/0.15),
    mSimTime(0.0),
    mNextReportTime(0.5),
    mReportInterval(0.5)   // drones report every 0.5 s
{
    // Register HQ node in the comms network
    mComms.addNode("HQ");
}

/*
 * @brief: 
 *         Creates a new drone, assigns it an ID, and registers it in the
 *         communication network.
 *
 * The drone ID corresponds to its index in the internal vector.
 * A matching network node ("Drone0", "Drone1", …) is also created so that
 * the drone may send telemetry messages.
 *
 * @param: parameters
 *         Initial drone configuration parameters.
 * @param: startPos 
 *         Starting position in world coordinates.
 * @return: The assigned drone ID.
 */

int Simulator::addDrone(const DroneParams& parameters, const Vector2& startPos) {
    int id = static_cast<int>(mDrones.size());   // id = index
    mDrones.emplace_back(id, parameters, startPos);

    // Create a node name like "Drone0", "Drone1", etc.
    std::string nodeName = "Drone" + std::to_string(id);
    mComms.addNode(nodeName);

    return id;
}

/**
 * @brief: 
 *         Sets the thrust direction for the specified drone.
 *
 * Performs bounds checking on the drone ID and forwards the command to
 * the drone instance.
 *
 * @param: droneId
 *         ID of the drone to command.
 * @param: direction
 *         Normalized direction vector for thrust.
 */
void Simulator::setDroneThrustDirection(int droneId, const Vector2& direction) {
    if (droneId >= 0 && droneId < static_cast<int>(mDrones.size())) {
        mDrones[droneId].setThrustDirection(direction);
    }
}

/*
 * @brief:
 *         Sets the full thrust force vector for a drone.
 *
 * Unlike setDroneThrustDirection(), this function directly adjusts both
 * direction and magnitude of the drone's thrust, providing more control.
 *
 * @param: droneId
 *         ID of the drone.
 * @param: force
 *         Thrust vector applied to the drone.
 */

void Simulator::setDroneThrustForce(int droneId, const Vector2& force) {
    if (droneId >= 0 && droneId < static_cast<int>(mDrones.size())) {
        mDrones[droneId].setThrustForce(force);
    }
}

/*
 * @brief: 
 *         Removes all thrust from a drone so that only gravity and external
 *         forces act upon it.
 *
 * @param: droneId 
 *         ID of the drone to modify.
 */

void Simulator::clearDroneThrust(int droneId) {
    if (droneId >= 0 && droneId < static_cast<int>(mDrones.size())) {
        mDrones[droneId].clearThrust();
    }
}

/*
 * @brief:
 *         Advances the physics simulation and communication system by dt seconds.
 *
 * Steps performed:
 * 1. Update each drone’s physics (position, velocity, forces).
 * 2. If the reporting interval has been reached, send a telemetry message
 *    for each drone.
 * 3. Step the communication network to deliver pending messages, simulate
 *    delays, jitter, and packet drops.
 *
 * @param: dt
 *         Time step in seconds.
 */
void Simulator::step(double dt) {
    mSimTime += dt;

    // 1) Update all drones (physics)
    for (auto& d : mDrones) {
        d.update(dt, mWorld);
    }

    // 2) Periodic status reports from each drone to HQ
    if (mSimTime >= mNextReportTime) {
        for (const auto& d : mDrones) {
            sendDroneStatus(d, mSimTime);
        }
        mNextReportTime += mReportInterval;
    }

    // 3) Advance comms network simulation
    mComms.step(mSimTime);
}


/*
 * @brief:
 *         Builds a telemetry status message for a drone and sends it to HQ.
 *
 * The message contains:
 * - Position (x, y)
 * - Velocity (x, y)
 *
 * Values are formatted to two decimal places for readability.
 *
 * @param: d 
 *         Reference to the drone generating the report.
 * @param: currentTime
 *         Simulation timestamp when the message is sent.
 */

void Simulator::sendDroneStatus(const Drone& d, double currentTime) {
    std::ostringstream oss;
    oss << "STATUS pos=("
        << std::fixed << std::setprecision(2)
        << d.getPosition().x << "," << d.getPosition().y << ") vel=("
        << d.getVelocity().x << "," << d.getVelocity().y << ")";

    std::string payload = oss.str();
    std::string fromName = "Drone" + std::to_string(d.getId());

    mComms.sendMessage(fromName, "HQ", payload, currentTime);
}

/*
 * @brief: 
 *         Prints a summary of all communication statistics recorded during
 *         the simulation.
 *
 * Includes:
 * - Number of messages sent
 * - Delivered vs. dropped messages
 * - Average latency
 * - Any additional logging produced by Network
 *
 * Called once at the end of main().
 */
void Simulator::printCommsSummary() const {
    mComms.printSummary(mSimTime);
}
