#include "page_graphics.h"

#include <cstdlib>
#include <cstdio>
#include <string.h>

#include <jpeglib.h>
#include <jerror.h>

using namespace PAGE;

GraphicsContext::GraphicsContext()
{
	height = 0;
	width = 0;
	meshes = std::vector<Mesh>();
}

void GraphicsContext::initialize(int h, int w)
{
//	glClearColor(0.0f,0.0f,0.0f,0.0f);
}

void GraphicsContext::release()
{
	//destroy_vbos();
}

void GraphicsContext::add_mesh(Mesh &mesh)
{
//	meshes.push_back(mesh);
//	create_vbo(mesh);
}

void GraphicsContext::create_vbo(Mesh &mesh)
{
}

void GraphicsContext::destroy_vbos()
{
/*	GLenum ErrorCheckValue = glGetError();

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		Debug::LogError("Could not destroy the VBOs");
		//Debug::LogError(gluErrorString(ErrorCheckValue));

		exit( EXIT_FAILURE );
	} */
}

// this function is based off of LoadShader() shown in class on 2/16/12
GLuint GraphicsContext::load_shader(const char* filename, GraphicsContext::Shader type)
{
/*	GLuint shader_id = 0;
	FILE* file;
	long file_size = -1;
	GLchar* glsl_source;

	GLenum shader_type;

	Debug::Log("Attempting to load shader file.");

	if (type == GraphicsContext::VERTEX)
		shader_type = GL_VERTEX_SHADER;
	if (type == GraphicsContext::FRAGMENT)
		shader_type = GL_FRAGMENT_SHADER;

	file = fopen(filename, "rb");
	if (file == NULL)
	{
		Debug::LogError(filename);
		Debug::LogError("Failed to open shader file.");

		return -1;
	}
	// assume file is open
	if (fseek(file, 0, SEEK_END) == 0)
	{
		Debug::LogError("Failed to seek through shader file.");
		return -1;
	}
	file_size = ftell(file); // grab the file size
	if (file_size == -1)
	{
		Debug::LogError(filename);
		Debug::LogError("File size is unknown.");

		return -1;
	}
	// assume we got a good file size
	rewind(file);
	glsl_source = (GLchar*)malloc(file_size+1); // allocate new memory for glsl
	if (file_size != (long)fread(glsl_source, sizeof(GLchar), file_size, file)) // read the data
	{
		Debug::LogError("Failed to properly read shader file.");

		return -1;
	}
	glsl_source[file_size] = '\0'; // set the last value to the null terminator
	const GLchar* glsl_source_c = glsl_source;
	if ((shader_id = glCreateShader(shader_type)) == 0)
	{
		Debug::LogError("Failed to create shader.");
		shader_id = -1;
	}
	else
	{
		glShaderSource(shader_id, 1, &glsl_source_c, NULL);
		glCompileShader(shader_id);
	}

	free(glsl_source);
	fclose(file);

	return shader_id; */
	return -1;
}
GLuint GraphicsContext::create_shader_program()
{
/*	current_program = glCreateProgram();
	programs.push_back(current_program);
	return current_program; */
	return 0;
}
void GraphicsContext::add_shader(GLuint id)
{
//	glAttachShader(current_program,id);
}
void GraphicsContext::link_program()
{
//	glLinkProgram(current_program);
}
GLint GraphicsContext::get_uniform_location(const char* name)
{
//	return glGetUniformLocation(current_program, name);
	return 0;
}

void GraphicsContext::bind_texture(Texture2D texture)
{
/*	GLuint texId;
	textures.push_back(texId);
	glGenTextures(1,&texId);

	glBindTexture( GL_TEXTURE_2D, texId );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture.UWrap());
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture.VWrap());
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture.MagFilter());
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture.MinFilter());

	// determine file type
	Texture2D::FileType type = texture.ImageType();
	if (type == Texture2D::TGA)
	{
		// use glfw's function
		if (!glfwLoadTexture2D( texture.Name(), 0 ))
			Debug::LogError("Failed to load texture.");
	}
	else if (type == Texture2D::JPEG)
	{
		unsigned char* pixels;
		pixels = (unsigned char*)malloc(3 * texture.Height() * texture.Width());
		unsigned char* line;
		struct jpeg_decompress_struct cinfo;
		struct jpeg_error_mgr jerr;

		cinfo.err = jpeg_std_error (&jerr);
		jpeg_create_decompress(&cinfo);

		FILE* file;
		if ((file = fopen(texture.Name(), "rb")) == NULL)
		{
			Debug::LogError("Failed to load texture.");
			exit( EXIT_FAILURE );
		}
		jpeg_stdio_src(&cinfo, file);
		jpeg_read_header(&cinfo, TRUE);

		GLenum format = texture.Format();
		if (GL_RGB == format)
		{
			if (cinfo.out_color_space == JCS_GRAYSCALE)
			{
				Debug::LogError("Conflicting format types detected (have RGB, found GRAYSCALE)");
				exit (EXIT_FAILURE);
			}
		}
		else
		{
			if (cinfo.out_color_space != JCS_GRAYSCALE)
			{
				Debug::LogError("Conflicting format types detected (have non RGB, found non GRAYSCALE)");

				exit (EXIT_FAILURE);
			}
		}
		jpeg_start_decompress(&cinfo);

		while (cinfo.output_scanline < cinfo.output_height);
		{
			line = pixels + (GL_RGB == format ? 3 * texture.Width() : texture.Width()) *
					cinfo.output_scanline;
			jpeg_read_scanlines ( &cinfo, &line, 1);
		}

		jpeg_finish_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);

		glTexImage2D(GL_TEXTURE_2D, 0, format,
				     texture.Width(), texture.Height(), 0,
				     format, GL_UNSIGNED_BYTE, pixels);
	} */
}
