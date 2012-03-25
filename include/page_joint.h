#ifndef __JOINT_H
#define __JOINT_H

#include "page_dof.h"
#include "page_matrix.h"
#include <string>
#include <vector>

namespace PAGE
{
    class Joint
    {
        public:
            Joint(std::string name = "Joint");
            virtual ~Joint();
            void set_bind_matrix(Matrix44 matrix);
            void set_local_matrix(Matrix44 matrix);
            Matrix44 get_bind_matrix();
            Matrix44f get_bind_matrixF();
            Matrix44 get_inverse_bind_matrix();
            Matrix44f get_inverse_bind_matrixF();
            Matrix44 get_local_matrix();
            Matrix44f get_local_matrixF();
            Matrix44 get_world_matrix();
            Matrix44f get_world_matrixF();
            void set_parent(Joint* parent);
            void add_child(Joint child);
			int get_num_children();
            Joint* get_child(std::string name);
            Joint* get_child(int i);
            void remove_child(std::string name);
            Joint* get_parent();
            void remove_parent();
            void update();
            void add_dof(DOF* dof);
            std::string get_name();
        private:
            std::string name;
            Joint* parent;
            DOF** dofs;
            std::vector<Joint*> children;
            Matrix44 local_matrix;
            Matrix44 world_matrix;
            Matrix44 bind_matrix;
            Matrix44 inverse_bind_matrix;
    };
}
#endif // __JOINT_H
