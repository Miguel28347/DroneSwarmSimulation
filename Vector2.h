#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

/*
* @class: 
*        Vector2
* @brief:
*        A 2D mathmatical vecto used for physics, movement, and geometry.
* 
* The Vector2 class provides essential tools for operating on two-dimensional vectors,
* including addition, subtraction, scalar multiplication, magnitude calculation, and normalization.
* It is the core building block of the physics engine (forces, velocity, acceleration, drone movement,
* collisions response).
* 
* All operations assume standard geometry.
*/

class Vector2 {

public:

    /*
    * @brief:
    *         The x-component of the vector.
    */

    double x;

    /*
    * @brief:
    *         The y-component of the vector. 
    */

    double y;

    /*
    * @brief:
    *         Contructs a zero vector (0,0).
    * @param: xVal
    *         Value of the x-component.
    * @param: yVal
    *         Value of the y-component.
    */

    Vector2() : x(0.0), y(0.0) {}

    /*
    * @brief:
    *         Contructs a vector with given components.
    * @param: xVal
    *         Value of the x-component.
    * @param: yVal
    *         Value of the y-component.
    */

    Vector2(double xVal, double yVal) : x(xVal), y(yVal) {}

    /*
    * @brief:
    *         Adds this vector to another and returns the result.
    * 
    * @param: other 
    *         The other value to add.
    * @return: A new Vector2 representing the sum. 
    */

    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    /*
    * @brief:
    *         Adds another vector to this one.
    * @param: other
    *         The vector to add.
    * @return: Reference to this vector. 
    */

    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    /*
    * @brief:
    *         Subtracts another vector from this one and returns the result.
    * @param: other
    *         The vector to subtract.
    * @return: A new Vector2 representing the difference. 
    */

    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    /*
    * brief:
    *         Multiplies this vector by scalar and returns the result.
    * 
    * @param: scalar
    *         The scalar multiplier.
    * @return: A new Vector2 representing the scaled vector.
    */

    Vector2 operator*(double scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    /*
    * @brief:
    *         Scales this vector in place by a scalar.
    * @param: scalar
    *         This is the scalar multiplier.
    * @return: Reference to this vector. 
    */

    Vector2& operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    /*
    * @brief:
    *         Computes the magnitude (length) of the vector.
    * @return: The Euclidean length sqrt(x² + y²).
    */

    double length() const {
        return std::sqrt(x * x + y * y);
    }

    /*
    * @brief:
    *         Returns a normalized unit length copy of the vector.
    * 
    * If the vector has a zero length, returns (0,0) to avoid division by zero.
    * 
    * @return: A normalized Vector2. 
    */

    Vector2 normalized() const {
        double len = length();
        if (len == 0.0) {
            return Vector2(0.0, 0.0);
        }
        return Vector2(x / len, y / len);
    }
};

#endif //VECTOR2_H
