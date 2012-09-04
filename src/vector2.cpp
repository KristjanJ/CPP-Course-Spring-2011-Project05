#include "vector2.h"

#include <iostream>
#include <sstream>
#include <cmath>

Vector2::Vector2(void)
{
    m_x = 0;
    m_y = 0;
}

Vector2::Vector2(int x, int y)
{
    m_x = x;
    m_y = y;
}

Vector2::Vector2(const Vector2& other)
{
    m_x = other.m_x;
    m_y = other.m_y;
}

Vector2::~Vector2(void)
{

}

float Vector2::distanceFrom(const Vector2& other) const
{
    float fNum = pow((m_x - other.m_x), 2) + pow((m_y - other.m_y), 2);

    float distance = sqrt(fNum);

    return distance;
}

float Vector2::distanceFrom(int x, int y) const
{
    float fNum = pow((m_x - x), 2) + pow((m_y - y), 2);

    float distance = sqrt(fNum);

    return distance;
}

std::string Vector2:: toString(void) const
{
    std::string vector2Info;
    std::string xStr;
    std::string yStr;

    std::ostringstream outStringStream;
    outStringStream << m_x;
    xStr = outStringStream.str();
    outStringStream.str("");
    outStringStream << m_y;
    yStr = outStringStream.str();

    vector2Info = "(" + xStr + ", " + yStr + ")";

    return vector2Info;
}

std::ostream& operator << (std::ostream& out, const Vector2& vector2)
{
    out << vector2.toString();

    return out;
}
