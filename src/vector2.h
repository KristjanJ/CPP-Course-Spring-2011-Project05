#ifndef VECTOR2_H
#define VECTOR2_H

#include <iosfwd>
#include <string>

/*!
\brief A 2D vector.
*/
class Vector2
{
public:
    /*!
    \details X coordinate of this vector.
    */
    int m_x;

    /*!
    \details Y coordinate of this vector.
    */
    int m_y;

    /*!
    \details Default constructor. Constructs a null vector.
    */
    Vector2(void);

    /*!
    \details Constructs a vector with the coordinates x and y.
    \param x X coordinate.
    \param y Y coordinate.
    */
    Vector2(int x, int y);

    /*!
    \details Copy constructor. Constructs a vector from another vector.
    \param other Another vector.
    */
    Vector2(const Vector2& other);

    /*!
    \details Destructs a vector.
    */
    ~Vector2(void);

    /*!
    \details Returns the distance between this vector and an another vector.
    \param other Another vector.
    \returns The distance between this vector and an another vector.
    */
    float distanceFrom(const Vector2& other) const;

    /*!
    \details Returns the distance between this vector and a point.
    \param x X coordinate of the point.
    \param y Y coordinate of the point.
    \returns The distance between this vector and a point.
    */
    float distanceFrom(int x, int y) const;

    /*!
    \details Returns a string representation of this vector.
    \returns A string representation of this vector.
    */
    std::string toString(void) const;
};

std::ostream& operator << (std::ostream& out, const Vector2& vector2);

#endif // VECTOR2_H
