#include "Drone.h"
#include <algorithm>

/*
 * @brief:
 *         Constructs a Drone and initializes its physical state.
 *
 * The drone starts with:
 * - Given ID and physical parameters
 * - Start position (x, y)
 * - Zero velocity
 * - Zero thrust
 *
 * @param: id
 *         Unique drone identifier.
 * @param: parameters
 *         Physical configuration parameters.
 * @param: startPos
 *         Initial world-space position.
 */

Drone::Drone(int id, const DroneParams& parameters, const Vector2& startPos)
    : mId(id),
    mParameters(parameters),
    mPosition(startPos),
    mVelocity(0.0, 0.0),
    mThrust(0.0, 0.0) {
}

/*
 * @brief: 
 *         Sets thrust by giving only a direction vector.
 *
 * The direction is normalized, then scaled to the drone's max thrust.
 * This is useful for simple directional controllers or steering behaviors.
 *
 * @param: direction 
 *         The desired thrust direction.
 */

void Drone::setThrustDirection(const Vector2& direction) {
    Vector2 dirNorm = direction.normalized();
    mThrust = dirNorm * mParameters.maxThrust;
}

/*
 * @brief: 
 *         Directly applies a thrust force vector.
 *
 * If |force| ? maxThrust, it is used directly.
 * Otherwise, it is scaled down (clamped) to the drone’s maximum allowed thrust.
 *
 * @param: force 
 *         Force vector to apply, in Newtons.
 */

void Drone::setThrustForce(const Vector2& force) {
    double mag = force.length();
    if (mag == 0.0 || mag <= mParameters.maxThrust) {
        mThrust = force;
    }
    else {
        // Clamp magnitude to maxThrust
        mThrust = force * (mParameters.maxThrust / mag);
    }
}

/*
 * @brief: 
           Removes all thrust, leaving gravity as the only active force.
 */

void Drone::clearThrust() {
    mThrust = Vector2(0.0, 0.0);
}

/*
 * @brief:
 *         Updates the drone's physics state using semi-implicit Euler integration.
 *
 * Physics pipeline:
 * 1. Compute total force = thrust + mass * gravity
 * 2. Compute acceleration = totalForce / mass
 * 3. Integrate velocity: v += a * dt
 * 4. Clamp velocity magnitude to maxSpeed (if enabled)
 * 5. Integrate position: x += v * dt
 * 6. Enforce world bounds (simple clamping with velocity cancellation)
 *
 * @param: dt    
 *         Timestep in seconds.
 * @param: world 
 *         Reference to global world settings (gravity, bounds).
 */

void Drone::update(double dt, const World& world) {
    // Total force = thrust + gravity * mass
    Vector2 gravityForce = world.gravity * mParameters.mass;
    Vector2 totalForce = mThrust + gravityForce;

    // a = F / m
    Vector2 acceleration = totalForce * (1.0 / mParameters.mass);

    // Semi-implicit Euler integrtation: v += a*dt, x += v*dt
    mVelocity += acceleration * dt;

    double speed = mVelocity.length();
    if (mParameters.maxSpeed > 0.0 && speed > mParameters.maxSpeed) {
        mVelocity = mVelocity * (mParameters.maxSpeed / speed);
    }
    // Position update
    mPosition += mVelocity * dt;

    // Boundary conditions
    if (mPosition.x < 0.0) { mPosition.x = 0.0; mVelocity.x = 0.0; }
    if (mPosition.y < 0.0) { mPosition.y = 0.0; mVelocity.y = 0.0; }
    if (mPosition.x > world.width) { mPosition.x = world.width;  mVelocity.x = 0.0; }
    if (mPosition.y > world.height) { mPosition.y = world.height; mVelocity.y = 0.0; }
}
