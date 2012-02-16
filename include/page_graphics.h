#ifndef __PAGE_GRAPHICS_H
#define __PAGE_GRAPHICS_H

#include "page_vector.h"
#include "page_mesh.h"
#include <fstream>
#include <vector>

namespace PAGE
{
	enum Shader { VERTEX, FRAGMENT };
	class GraphicsContext
	{
		public:
			GraphicsContext();
			void initialize(int h, int w);
			void initialize(Vector2 &resolution) { initialize(resolution.x,resolution.y); }
			void release();

			void set_clear_color(float r, float g, float b, float a);
			void set_clear_color(Vector4 &rgba);
			bool add_program(int program_id);
			bool add_shader(std::ifstream& shader, int program_id, Shader shader_type);
			bool add_shader(const char* shader, int program_id);

			void add_mesh(Mesh &mesh);

			void render();

		private:
			void create_vbo(Mesh &mesh);

			void destroy_vbos();
			std::vector<Mesh> meshes;
			int height;
			int width;
	};
}

#endif
