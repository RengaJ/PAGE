#ifndef __ANIMATION_H
#define __ANIMATION_H

#include "page_utility.h"
#include "page_animationjoint.h"

namespace PAGE
{
    class Animation
    {
        public:
            Animation(std::string name="default");

            void set_name(std::string name);
            void set_fps(int fps);
            void set_order(AnimationOrder a_order);
            void set_order(const char* pattern);

            void add_joint(AnimationJoint joint);
            void add_joint(const char* name);
            void add_joint(std::string name);

			AnimationJoint* get_joint(const char* name);
            AnimationJoint* get_joint(std::string name);
            AnimationJoint* get_joint(int joint_index);

            int get_fps();
            std::string get_name();
            AnimationOrder get_order();

            Animation& operator=(const Animation &anim);
            friend std::ostream& operator<<(std::ostream& out, Animation& animation)
            {
            	out << "Animation Name: " << animation.name << std::endl;
				out << "Frames Per Second: " << animation.fps << std::endl;
				out << "Animation Order: " << animation.order << std::endl;
				out << "Joints:\n";
				for (int i = 0; i < animation.joints.size(); i++)
					out << animation.joints[i] << std::endl;

				return out;
            }
        protected:
        private:
			AnimationOrder order;
            int fps;
            std::string name;
            std::vector<AnimationJoint> joints;
    };
}
#endif // __ANIMATION_H
