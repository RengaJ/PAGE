#include "page_animation.h"

using namespace PAGE;
Animation::Animation(std::string name)
{
    this->name = name;
    fps = 24;
}
void Animation::set_name(std::string name)
{
	this->name = name;
}
void Animation::set_fps(int fps)
{
	this->fps = fps;
}
void Animation::set_order(AnimationOrder a_order)
{
	order = a_order;
}
void Animation::set_order(const char* pattern)
{
	if (strncmp(pattern,"sphrt",5) == 0) order = SPHRT;
	else if (strncmp(pattern,"sprht",5) == 0) order = SPRHT;
	else if (strncmp(pattern,"shprt",5) == 0) order = SHPRT;
	else if (strncmp(pattern,"shrpt",5) == 0) order = SHRPT;
	else if (strncmp(pattern,"srhpt",5) == 0) order = SRHPT;
	else if (strncmp(pattern,"srpht",5) == 0) order = SRPHT;
}
void Animation::add_joint(AnimationJoint joint)
{
	joints.push_back(joint);
}
void Animation::add_joint(const char* name)
{
	joints.push_back(AnimationJoint(std::string(name)));
}
void Animation::add_joint(std::string name)
{
	joints.push_back(AnimationJoint(name));
}
int Animation::get_fps()
{
	return fps;
}
std::string Animation::get_name()
{
	return name;
}
AnimationOrder Animation::get_order()
{
	return order;
}
AnimationJoint* Animation::get_joint(const char* name)
{
	for (int i = 0; i < joints.size(); i++)
		if (strncmp(name, joints[i].get_name().c_str(), strlen(name)) == 0)
			return &joints[i];
	return &joints[0];
}
AnimationJoint* Animation::get_joint(std::string name)
{
	for (int i = 0; i < joints.size(); i++)
	{
		if (name == joints[i].get_name())
			return &joints[i];
	}
	return &joints[0];
}
AnimationJoint* Animation::get_joint(int joint_index)
{
	if (joint_index < 0 || joint_index >= joints.size())
		return &joints[0];
	return &joints[joint_index];
}
Animation& Animation::operator=(const Animation &anim)
{
	if (this == &anim)
		return *this;
	this->fps = anim.fps;
	this->order = anim.order;
	this->name = anim.name;
}
