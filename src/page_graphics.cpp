#include "page_graphics.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/glfw.h>

using namespace PAGE;

GraphicsContext::GraphicsContext()
{
	height = 0;
	width = 0;
	meshes = std::vector<Mesh>();
}

void GraphicsContext::initialize(int h, int w)
{
	glClearColor(0.0f,0.0f,0.0f,0.0f);
}

void GraphicsContext::release()
{
	destroy_vbos();
}

void GraphicsContext::add_mesh(Mesh &mesh)
{
	meshes.push_back(mesh);
	create_vbo(mesh);
}

void GraphicsContext::create_vbo(Mesh &mesh)
{
}

void GraphicsContext::destroy_vbos()
{
	GLenum ErrorCheckValue = glGetError();

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		Debug::LogError("Could not destroy the VBOs");
		//Debug::LogError(gluErrorString(ErrorCheckValue));

		exit( EXIT_FAILURE );
	}
}
