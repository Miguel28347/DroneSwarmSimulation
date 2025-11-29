#ifndef WORLD_H
#define WORLD_H

#include "Vector2.h"

/*
* @class:
         World
* @brief:
*        Defines global simulation parameters used by the physics engine.
* 
* The World class stores high-level environmental settings such as gravity and the physical 
* boundaries of the simulated environment. All physics calculations particle motion, drone movement,
* collisions, and forces depend on the configuration stored in this object. 
* 
* Usage:
* - Provides a shared World instance to physics components.
* - Configure custom gravity for specialized simulations (e.g lunar gravity)
* - Adjust width/ height to define the simulation bounding box. 
* 
* @notes:
* This class does not enforce boundary checking. It only stores the values. Collisions or 
* boundaries enforcement is handled in Vector2.  
*/
class World {
public:

    /*
    * @brief:
    *         Gravity vector applied globally to all physics bodies.
    * 
    * Units are assumed to be meters per second (m/s²).
    * Default is Earth's gravitational acceleration (0, -9.8)
    */

    Vector2 gravity;

    /*
    * @brief:
    *         The width of the simulation world in meters.
    * 
    * Used to define the horizontal boundaries for object movement. 
    */

    double width;

    /*
    * @brief:
    *         The height of the simulation world in meters. 
    * 
    * Represents the upper and lower vertical limits of the simulation. 
    */

    double height;

    /*
    * @brief:
    *         Default constructor.
    * 
    * Initializes the world with (0, -9.8).
    * World size of 100m x 100m
    */

    World()
        : gravity(0.0, -9.8),
        width(100.0),
        height(100.0) {
    }

    /*
    * @brief:
    *         Constructs a world with custom gravity and bounds.
    * 
    * @param: gravityVal
    *         The gravity vector to apply.
    * @param: w
    *         World width in meters.
    * @param: h
    *        World height in meters. 
    */

    World(const Vector2& gravityVal, double w, double h)
        : gravity(gravityVal), width(w), height(h) {
    }
};

#endif // WORLD_H
