#include "page_joint.h"

using namespace PAGE;

Joint::Joint(std::string name)
{
    this->name = name;
    bind_matrix = Matrix44(1.0f);
    inverse_bind_matrix = bind_matrix.inverse();
    parent = NULL;
    dofs = new DOF*[6];
    dofs[0] = new XDOF(0,0);
    dofs[1] = new YDOF(0,0);
    dofs[2] = new ZDOF(0,0);
    dofs[3] = new HDOF(0,0,false);
    dofs[4] = new PDOF(0,0,false);
    dofs[5] = new RDOF(0,0,false);

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
void Joint::set_local_matrix(Matrix44 matrix)
{
	local_matrix = matrix;
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
Matrix44 Joint::get_local_matrix()
{
	return local_matrix;
}
Matrix44f Joint::get_local_matrixF()
{
	return local_matrix.toArray();
}
Matrix44 Joint::get_world_matrix()
{
	return world_matrix;
}
Matrix44f Joint::get_world_matrixF()
{
	return world_matrix.toArray();
}
void Joint::set_parent(Joint* parent)
{
    this->parent = parent;
}
void Joint::add_child(Joint child)
{
    children.push_back(&child);
    children[children.size()-1]->set_parent(this);
}

int Joint::get_num_children()
{
	return children.size();
}

Joint* Joint::get_child(std::string name)
{
    for (int i = 0; i < children.size(); i++)
        if (name.compare(children[i]->get_name()) == 0)
            return children[i];
    return NULL;
}

Joint* Joint::get_child(int index)
{
	if (index < 0 || index > children.size())
		return NULL;
	return children[index];
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
	// local matrix has already been defined
	Matrix44 world_parent = Matrix44(1.0f);
	if (parent != NULL)
		world_parent = parent->get_world_matrix();
	world_matrix = world_parent * local_matrix;
    for (int i = 0; i < children.size(); i++)
        children[i]->update();
}

void Joint::add_dof(DOF* dof)
{
    *(dofs[dof->get_constraint()]) = *dof;
}

std::string Joint::get_name()
{
    return name;
}
