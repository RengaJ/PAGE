#include "page_dof.h"
#include "page_utility.h"

using namespace PAGE;

DOF::DOF(float min, float max, Freedom constraint)
{
    // just in case the user decides to be annoying...
    if (min <= max)
    {
        min_value = min;
        max_value = max;
    }
    else
    {
        min_value = max;
        max_value = min;
    }
    m_constraint = constraint;
}

// Assignment Operator
DOF& DOF::operator=(const DOF& rhs)
{
    if (this == &rhs) return *this;

    m_value = rhs.m_value;
    min_value = rhs.min_value;
    max_value = rhs.max_value;
    m_constraint = rhs.m_constraint;

    return *this;
}

void DOF::set_min_max(float min, float max)
{
    if (min <= max)
    {
        min_value = min;
        max_value = max;
    }
    else // just in case the user decided to be annoying...
    {
        min_value = max;
        max_value = min;
    }
}

void DOF::set_value(float value)
{
    m_value = clampf(value, min_value, max_value);
}

float DOF::get_value() { return m_value; }
float DOF::get_min() { return min_value; }
float DOF::get_max() { return max_value; }

DOF::Freedom DOF::get_constraint() { return m_constraint; }

XDOF::XDOF(float min, float max)
    : DOF(min,max,X)
{
    m_value = 0.0f;
}
Matrix44 XDOF::toMatrix()
{
    Matrix44 matrix = Matrix44(1.0f);
    matrix[3][0] = m_value;

    return matrix;
}
YDOF::YDOF(float min, float max)
    : DOF(min,max,Y)
{
    m_value = 0.0f;
}
Matrix44 YDOF::toMatrix()
{
    Matrix44 matrix = Matrix44(1.0f);
    matrix[3][1] = m_value;

    return matrix;
}
ZDOF::ZDOF(float min, float max)
    : DOF(min,max,Z)
{
    m_value = 0.0f;
}
Matrix44 ZDOF::toMatrix()
{
    Matrix44 matrix = Matrix44(1.0f);
    matrix[3][2] = m_value;

    return matrix;
}
HDOF::HDOF(float min, float max, bool degrees)
    : DOF(min,max,H)
{
    if (degrees)
    {
        min_value *= DEG_TO_RAD;
        max_value *= DEG_TO_RAD;
    }
    min_value = clampf(min,0,max);
    max_value = clampf(max,min,FULL_ANGLE_RAD);

    m_value = 0.0f;
}
void HDOF::set_value_degrees(float value)
{
    value *= DEG_TO_RAD;
    m_value = clampf(value,min_value,max_value);
}
float HDOF::get_value_degrees()
{
    return m_value * RAD_TO_DEG;
}
float HDOF::get_min_degrees()
{
    return min_value * RAD_TO_DEG;
}
float HDOF::get_max_degrees()
{
    return max_value * RAD_TO_DEG;
}
Matrix44 HDOF::toMatrix()
{
    Matrix44 matrix = Matrix44(1.0f);
    matrix[0][0] = (float)cos(m_value);
    matrix[2][0] = (float)sin(m_value);
    matrix[0][2] = (float)(-1 * sin(m_value));
    matrix[2][2] = (float)cos(m_value);

    return matrix;
}
PDOF::PDOF(float min, float max, bool degrees)
    : DOF(min,max,P)
{
    if (degrees)
    {
        min_value *= DEG_TO_RAD;
        max_value *= DEG_TO_RAD;
    }
    min_value = clampf(min,0,max);
    max_value = clampf(max,min,FULL_ANGLE_RAD);

    m_value = 0.0f;
}
void PDOF::set_value_degrees(float value)
{
    value *= DEG_TO_RAD;
    m_value = clampf(value,min_value,max_value);
}
float PDOF::get_value_degrees()
{
    return m_value * RAD_TO_DEG;
}
float PDOF::get_min_degrees()
{
    return min_value * RAD_TO_DEG;
}
float PDOF::get_max_degrees()
{
    return max_value * RAD_TO_DEG;
}
Matrix44 PDOF::toMatrix()
{
    Matrix44 matrix = Matrix44(1.0f);
    matrix[1][1] = (float)cos(m_value);
    matrix[2][1] = (float)(-1 * sin(m_value));
    matrix[1][2] = (float)sin(m_value);
    matrix[2][2] = (float)cos(m_value);

    return matrix;
}
RDOF::RDOF(float min, float max, bool degrees)
    : DOF(min,max,R)
{
    if (degrees)
    {
        min_value *= DEG_TO_RAD;
        max_value *= DEG_TO_RAD;
    }
    min_value = clampf(min,0,max);
    max_value = clampf(max,min,FULL_ANGLE_RAD);

    m_value = 0.0f;
}
void RDOF::set_value_degrees(float value)
{
    value *= DEG_TO_RAD;
    m_value = clampf(value,min_value,max_value);
}
float RDOF::get_value_degrees()
{
    return m_value * RAD_TO_DEG;
}
float RDOF::get_min_degrees()
{
    return min_value * RAD_TO_DEG;
}
float RDOF::get_max_degrees()
{
    return max_value * RAD_TO_DEG;
}
Matrix44 RDOF::toMatrix()
{
    Matrix44 matrix = Matrix44(1.0f);
    matrix[0][0] = (float)cos(m_value);
    matrix[1][0] = (float)(-1 * sin(m_value));
    matrix[0][1] = (float)sin(m_value);
    matrix[1][1] = (float)cos(m_value);

    return matrix;
}
