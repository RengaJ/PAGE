#ifndef __PAGE_GRAPHICS_H
#define __PAGE_GRAPHICS_H

#include "page_vector.h"
#include "page_mesh.h"
#include "page_texture.h"

#include <vector>

#include <GL/glew.h>
#include <GL/glfw.h>

namespace PAGE
{
	class GraphicsContext
	{
		public:
			enum Shader { VERTEX = 1, FRAGMENT = 2 };

			GraphicsContext();
			void initialize(int h, int w);
			void initialize(Vector2 &resolution) { initialize(resolution.x,resolution.y); }
			void release();

			void add_mesh(Mesh &mesh);

			void render();

			GLuint load_shader(const char* filename, Shader type);
			GLuint create_shader_program();
			void add_shader(GLuint id);
			void link_program();
			GLint get_uniform_location(const char* name);

			void bind_texture(Texture2D texture);
		private:
			void create_vbo(Mesh &mesh);

			void destroy_vbos();
			std::vector<GLuint> programs;
			std::vector<Mesh> meshes;
			std::vector<GLuint> textures;
			GLuint current_program;
			int height;
			int width;
	};
}

#endif
