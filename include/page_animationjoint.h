#ifndef __ANIMATION_JOINT_H
#define __ANIMATION_JOINT_H

#include "page_dof.h"
#include <vector>
#include <map>

namespace PAGE
{
	class AnimationJoint
	{
		public:
			AnimationJoint(std::string name = "default");

			void set_name(std::string name);
			void add_frame(DOF::Freedom dof, float value); // adds one frame with DOF value
			void add_frames(int n_frames, DOF::Freedom dof, float value); // add n_frames of DOF value
			void set_frame(DOF::Freedom dof, float value, int frame = -1); // sets the DOF value at given frame
			void set_frames(DOF::Freedom dof, float value, int f_frame, int t_frame = -1); // sets DOF value at [f_frame, t_frame)
			std::map<DOF::Freedom, float> get_frame_slice(int frame); // gets DOF data frame slice

			int frames(); // returns the current stored number of frames

			Matrix44 get_frame_matrix(int frame); // gets the matrix represented by the DOFS

			friend std::ostream& operator<<(std::ostream &out, AnimationJoint &joint)
			{
				out << "Joint Name: " << joint.joint_name << std::endl;
				out << "Frame Values: \n";
				for (int i = 0; i < joint.dof_values.size(); i++)
					for (std::map<DOF::Freedom, float>::iterator itr = joint.dof_values[i].begin();
							itr != joint.dof_values[i].end(); itr++)
							out << "DOF [" << itr->first << "] :: " << itr->second << std::endl;
				return out;
			}

			std::string get_name();
		protected:
		private:
			std::string joint_name;
			std::vector<std::map<DOF::Freedom, float> > dof_values;
	};
}
#endif // __ANIMATION_JOINT_H
