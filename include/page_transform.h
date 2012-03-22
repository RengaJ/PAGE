#ifndef __TRANSFORM_H
#define __TRANSFORM_H

#include "page_matrix.h"

namespace PAGE
{
    class Transform
    {
        public:
            Transform();
            // translate
            void translate(Vector3 xyz_translation);
            void translate(float dX, float dY=0.0f, float dZ=0.0f);
            // rotation (in radians)
            void rotate(Vector3 hpr_rotation);
            void rotate(float dH, float dP=0.0f, float dR=0.0f);
            // rotation (in degrees)
            void rotate_degrees(Vector3 hpr_rotation);
            void rotate_degrees(float dH, float dP=0.0f, float dR=0.0f);
            // scale
            void scale(float scalar);

            // return the position
            Vector3 position();
            Vector3 rotation();
            Vector3 rotation_degrees();
            float scale();
            Matrix44 matrix();
        private:
            Matrix44 m_matrix;
            Vector3 m_rotations;
            float m_scale;
    };
}

#endif // __TRANSFORM_H
