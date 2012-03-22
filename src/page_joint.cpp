#include "page_joint.h"

using namespace PAGE;

Joint::Joint(std::string name)
{
    this->name = name;
    bind_matrix = Matrix44(1.0f);
    inverse_bind_matrix = bind_matrix.inverse();
    parent = NULL;
    dofs = new DOF*[6];
    for (int i = 0; i < 6; i++)
        dofs[i] = NULL;

    local_matrix = Matrix44(1.0f);
    world_matrix = Matrix44(1.0f);
}

Joint::~Joint()
{
    delete [] dofs;
}

void Joint::set_bind_matrix(Matrix44 matrix)
{
    bind_matrix = matrix;
    inverse_bind_matrix = Matrix44::inverse(bind_matrix);
}
Matrix44 Joint::get_bind_matrix()
{
    return bind_matrix;
}
Matrix44f Joint::get_bind_matrixF()
{
    return bind_matrix.toArray();
}
Matrix44 Joint::get_inverse_bind_matrix()
{
    return inverse_bind_matrix;
}
Matrix44f Joint::get_inverse_bind_matrixF()
{
    return inverse_bind_matrix.toArray();
}

void Joint::set_parent(Joint* parent)
{
    this->parent = parent;
}
void Joint::add_child(Joint* child)
{
    children.push_back(child);
}

Joint* Joint::get_child(std::string name)
{
    for (int i = 0; i < children.size(); i++)
        if (name.compare(children[i]->get_name()) == 0)
            return children[i];
    return NULL;
}
void Joint::remove_child(std::string name)
{
    std::vector<Joint*>::iterator itr = children.begin();
    while (itr != children.end())
    {
        if (name.compare((*itr)->get_name()) == 0)
            break;
    }
    if (itr != children.end())
        children.erase(itr);
}

Joint* Joint::get_parent()
{
    return parent;
}
void Joint::remove_parent()
{
    parent = NULL;
}

void Joint::update()
{
    for (int i = 0; i < children.size(); i++)
        children[i]->update();
}

void Joint::add_dof(DOF* dof)
{
    for (int i = 0; i < 6; i++)
    {
        if (dofs[i] == NULL)
        {
            dofs[i] = dof;
            break;
        }
        // Since we are here, we know that dofs[i] != NULL
        if (dof->get_constraint() == dofs[i]->get_constraint())
        {
            dofs[i] = dof;
            break;
        }
    }
}

std::string Joint::get_name()
{
    return name;
}
