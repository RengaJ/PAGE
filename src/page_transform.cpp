#include "page_transform.h"

using namespace PAGE;

Transform::Transform()
{
    m_matrix = Matrix44(1.0f);
}

// translate
void Transform::translate(Vector3 xyz_translation)
{
    translate(xyz_translation.x,xyz_translation.y,xyz_translation.z);
}
void Transform::translate(float dX, float dY, float dZ)
{
    Matrix44 translation_matrix = Matrix44(1.0f);
    translation_matrix[3][0] = dX;
    translation_matrix[3][1] = dY;
    translation_matrix[3][2] = dZ;

    m_matrix = m_matrix * translation_matrix;
}
// rotation (in radians)
void Transform::rotate(Vector3 hpr_rotation)
{
    rotate(hpr_rotation.x,hpr_rotation.y,hpr_rotation.z);
}
void Transform::rotate(float dH, float dP, float dR)
{
    Matrix44 rotateH_matrix = Matrix44(1.0f);
    Matrix44 rotateP_matrix = Matrix44(1.0f);
    Matrix44 rotateR_matrix = Matrix44(1.0f);
    if (dH != 0.0f)
    {
        rotateH_matrix[0][0] = (float)cos(dH);
        rotateH_matrix[2][0] = (float)sin(dH);
        rotateH_matrix[0][2] = (float)(-1 * sin(dH));
        rotateH_matrix[2][2] = (float)cos(dH);
    }
    if (dP != 0.0f)
    {
        rotateP_matrix[1][1] = (float)cos(dP);
        rotateP_matrix[2][1] = (float)(-1 * sin(dP));
        rotateP_matrix[1][2] = (float)sin(dP);
        rotateP_matrix[2][2] = (float)cos(dP);
    }
    if (dR != 0.0f)
    {
        rotateR_matrix[0][0] = (float)cos(dR);
        rotateR_matrix[1][0] = (float)(-1 * sin(dR));
        rotateR_matrix[0][1] = (float)sin(dR);
        rotateR_matrix[1][1] = (float)cos(dR);
    }

    Matrix44 rotation_matrix = Matrix44(1.0f);
    rotation_matrix = rotation_matrix * rotateH_matrix;
    rotation_matrix = rotation_matrix * rotateP_matrix;
    rotation_matrix = rotation_matrix * rotateR_matrix;

    m_matrix = m_matrix * rotation_matrix;

    m_rotations.x += dH;
    m_rotations.y += dP;
    m_rotations.z += dR;
}
// rotation (in degrees)
void Transform::rotate_degrees(Vector3 hpr_rotation)
{
    hpr_rotation = hpr_rotation * DEG_TO_RAD;
    rotate(hpr_rotation.x,hpr_rotation.y, hpr_rotation.z);
}
void Transform::rotate_degrees(float dH, float dP, float dR)
{
    dH *= DEG_TO_RAD;
    dP *= DEG_TO_RAD;
    dR *= DEG_TO_RAD;

    rotate(dH,dP,dR); // just use the radian version of rotate
}
// scale
void Transform::scale(float scalar)
{
    Matrix44 scale_matrix = Matrix44(scalar);
    scale_matrix[3][3] = 1.0f;

    m_matrix = m_matrix * scale_matrix;
}

// return the position
Vector3 Transform::position()
{
    return m_matrix[3].toVector3();
}
Vector3 Transform::rotation()
{
    return m_rotations;
}
Vector3 Transform::rotation_degrees()
{
    return m_rotations * RAD_TO_DEG;
}
float Transform::scale() { return m_scale; }
Matrix44 Transform::matrix() { return m_matrix; }
