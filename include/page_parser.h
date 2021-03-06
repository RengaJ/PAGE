#ifndef __PAGE_PARSER_H
#define __PAGE_PARSER_H

#include "page_mesh.h"
#include "page_joint.h"
#include "page_utility.h"
#include "page_animation.h"
#include <fstream>

namespace PAGE
{
	namespace Parser
	{
        bool parse_egg(const char* filename, Mesh* mesh, GLenum render_type = GL_TRIANGLES, bool offset = true);
        void parse_egg_animation(const char* filename, char* animation_name, Mesh* mesh);
        void __parse_egg_texture(std::ifstream &file, Mesh* mesh);
        void __parse_egg_vertex(std::ifstream &file, Mesh* mesh);
        void __parse_egg_polygon(std::ifstream &file, Mesh* mesh);
        void __parse_egg_skeleton(char* name, std::ifstream &file, Mesh* mesh);
		Joint __parse_egg_joint(char* name, std::ifstream &file, Mesh* mesh);
        void __parse_egg_animation_joint(std::ifstream &file, const char* joint_name, Animation *anim, Mesh* mesh);
	}
}
#endif
