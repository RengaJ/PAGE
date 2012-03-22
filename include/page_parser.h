#ifndef __PAGE_PARSER_H
#define __PAGE_PARSER_H

#include "page_mesh.h"
#include <fstream>

namespace PAGE
{
	namespace Parser
	{
        void parse_egg(const char* filename, Mesh* mesh);
        void __parse_egg_texture(std::ifstream &file, Mesh* mesh);
        void __parse_egg_vertex(std::ifstream &file, Mesh* mesh);
        void __parse_egg_triangle(std::ifstream &file, Mesh* mesh);
        void __parse_egg_skeleton();
        void __parse_egg_animation(const char* filename, char* animation_name, Mesh* mesh);
	}
}
#endif
