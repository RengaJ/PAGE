#ifndef __DOF_H
#define __DOF_H

#include "page_matrix.h"

namespace PAGE
{
    class DOF
    {
        public:
            enum Freedom { X = 0, Y = 1, Z = 2, H = 3, P = 4, R = 5 };
            DOF& operator=(const DOF& other);

            void virtual set_value(float value);
            void virtual set_min_max(float min, float max);

            float get_value();
            float get_min();
            float get_max();

            Freedom get_constraint();
            static DOF::Freedom get_constraint(char axis)
			{
				if (axis == 'x') return DOF::X;
				if (axis == 'y') return DOF::Y;
				if (axis == 'z') return DOF::Z;
				if (axis == 'h') return DOF::H;
				if (axis == 'p') return DOF::P;
				if (axis == 'r') return DOF::R;
				return DOF::X;
			}
            Matrix44 virtual toMatrix() = 0;

        protected:
            DOF(float min, float max, Freedom constraint);
            Freedom m_constraint;
            float m_value;
            float min_value;
            float max_value;
    };

    class XDOF : public DOF
    {
        public:
            XDOF(float min, float max);
            Matrix44 virtual toMatrix();
    };

    class YDOF : public DOF
    {
        public:
            YDOF(float min, float max);
            Matrix44 virtual toMatrix();
    };

    class ZDOF : public DOF
    {
        public:
            ZDOF(float min, float max);
            Matrix44 virtual toMatrix();
    };

    class HDOF : public DOF
    {
        public:
            HDOF(float min, float max, bool degrees);
            void set_value_degrees(float value);
            float get_value_degrees();
            float get_min_degrees();
            float get_max_degrees();
            Matrix44 virtual toMatrix();
    };

    class PDOF : public DOF
    {
        public:
            PDOF(float min, float max, bool degrees);
            void set_value_degrees(float value);
            float get_value_degrees();
            float get_min_degrees();
            float get_max_degrees();
            Matrix44 virtual toMatrix();
    };

    class RDOF : public DOF
    {
        public:
            RDOF(float min, float max, bool degrees);
            void set_value_degrees(float value);
            float get_value_degrees();
            float get_min_degrees();
            float get_max_degrees();
            Matrix44 virtual toMatrix();
    };
}
#endif // __DOF_H
