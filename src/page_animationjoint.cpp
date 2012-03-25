#include "page_animationjoint.h"

using namespace PAGE;

AnimationJoint::AnimationJoint(std::string name)
{
	joint_name = name;
	dof_values = std::vector<std::map<DOF::Freedom, float> >();
}

void AnimationJoint::set_name(std::string name)
{
	joint_name = name;
}
void AnimationJoint::add_frame(DOF::Freedom dof, float value) // adds one frame with DOF value
{
	dof_values.push_back(std::map<DOF::Freedom, float>());
	for (int i = (int)DOF::X; i <= (int)DOF::R; ++i)
		dof_values[dof_values.size()-1][(DOF::Freedom)i] = 0.0f;
	dof_values[dof_values.size()-1][dof] = value;
}
void AnimationJoint::add_frames(int n_frames, DOF::Freedom dof, float value) // add n_frames of DOF value
{
	for (int i = 0; i < n_frames; i++)
		set_frame(dof, value,i);
}
void AnimationJoint::set_frame(DOF::Freedom dof, float value, int frame) // sets the DOF value at given frame
{
	if (frame < 0)
		frame = dof_values.size();
	if (frame >= dof_values.size())
		add_frame(dof, value);
	else
		dof_values[frame][dof] = value;
}
void AnimationJoint::set_frames(DOF::Freedom dof, float value, int f_frame, int t_frame) // sets DOF value at [f_frame, t_frame)
{
	if (dof_values.size() != 0)
	{
		f_frame = clampi(f_frame,0,dof_values.size());
		t_frame = clampi(t_frame,t_frame,dof_values.size());
		if (t_frame < 0) t_frame = dof_values.size();
	}
	else
	{
		f_frame = 0;
		t_frame = 1;
	}
	for (int i = f_frame; i < t_frame; i++)
		set_frame(dof,value,i);
}
std::map<DOF::Freedom, float> AnimationJoint::get_frame_slice(int frame) // gets DOF data frame slice
{
	if (frame < 0 || frame >= dof_values.size())
		return std::map<DOF::Freedom, float>();
	return dof_values[frame];
}

int AnimationJoint::frames() // returns the current stored number of frames
{
	dof_values.size();
}

std::string AnimationJoint::get_name()
{
	return joint_name;
}
