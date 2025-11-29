#ifndef DRONE_H
#define DRONE_H

#include "Vector2.h"
#include "World.h"

/*
 * @struct:
 *          DroneParams
 * @brief:
 *          Physical and performance parameters used to configure a drone.
 *
 * These values define the core physical behavior of each drone:
 * - mass        : Used for Newtonian integration (F = m·a)
 * - maxThrust   : Maximum force the drone can apply in any direction
 * - maxSpeed    : Optional speed clamp (0 = unlimited)
 */

struct DroneParams {
    double mass;        // kg
    double maxThrust;   // max thrust magnitude (N)
    double maxSpeed;    // max speed (m/s), 0 = no clamping
};

/*
 * @class:
 *         Drone
 * @brief:
 *         Represents a single physical drone in the 2D simulation.
 *
 * A Drone tracks its:
 * - Position and velocity
 * - Applied thrust force (vector)
 * - Physical parameters (mass, thrust limits)
 *
 * Responsibilities:
 * - Accept thrust direction or full thrust force commands.
 * - Clamp thrust to safe limits defined in DroneParams.
 * - Integrate motion using Newton’s laws (F = m·a) in update().
 *
 * The Simulator owns and updates Drone objects each timestep.
 */

class Drone {
public:

    /*
     * @brief: 
     *         Constructs a drone with a unique ID, parameter set, and start position.
     *
     * @param: id
     *        Unique drone identifier.
     * @param: parameters
     *          Physical and control parameters for the drone.
     * @param: startPos
     *         Initial position in world coordinates.
     */

    Drone(int id, const DroneParams& parameters, const Vector2& startPos);

    /**
     * @brief: 
     *         Sets thrust by specifying only a direction vector.
     *
     * The direction is normalized and scaled to maxThrust.
     * Useful for high-level steering or AI controllers.
     *
     * @param: direction
     *         Direction in which thrust is applied.
     */
    void setThrustDirection(const Vector2& direction);

    /*
     * @brief: 
     *         Directly sets the thrust force vector applied to the drone.
     *
     * The provided force will be clamped to maxThrust.
     * Suitable for physics-based controllers that output force or acceleration.
     *
     * @param: force 
     *        Thrust force vector in Newtons.
     */

    void setThrustForce(const Vector2& force);

    /*
     * @brief:
     *         Removes all thrust, leaving gravity and other forces as the only influences.
     */

    void clearThrust();

    /*
     * @brief: 
     *         Advances the drone’s physics state by dt seconds.
     *
     * Applies Newtonian physics:
     * - Compute acceleration = (thrust + gravity·mass) / mass
     * - Integrate velocity and clamp to maxSpeed if necessary
     * - Update position
     *
     * @param: dt
     *         Timestep in seconds.
     * @param: world
     *         Global world settings (gravity, bounds).
     */

    void update(double dt, const World& world);

    /*
     * @return: Drone’s unique identifier.
     */

    int getId() const { return mId; }

    /*
     * @return: Current position of the drone.
     */

    const Vector2& getPosition() const { return mPosition; }

    /*
     * @return: Current velocity of the drone.
     */

    const Vector2& getVelocity() const { return mVelocity; }

private:
    int mId;                 // Unique drone ID
    DroneParams mParameters; // Physical parameters 

    Vector2 mPosition;       // Current world postion
    Vector2 mVelocity;       // Current velocity

    Vector2 mThrust;         // thrust force in world coordinates (N)
};

#endif // DRONE_H
