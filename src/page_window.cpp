#include "page_window.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/glfw.h>

using namespace PAGE;

WindowContext::WindowContext()
{
	height = 0;
	width = 0;
	contexts = std::vector<GraphicsContext>();
}

void WindowContext::initialize( int h, int w )
{
	GLenum GlewInitResult;

	if (!glfwInit())
	{
		Debug::LogError("Failed to initialize GLFW");
		exit( EXIT_FAILURE );
	}

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);
	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	if (!glfwOpenWindow(w,h, 0,0,0,0, 16,0, GLFW_WINDOW))
	{
		Debug::LogError("Failed to open GLFW window");
		glfwTerminate();
		exit( EXIT_FAILURE );
	}

	glewExperimental = GL_TRUE;
	GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult)
	{
	//	Debug::LogError(glewGetErrorString(GlewInitResult));
		exit( EXIT_FAILURE );
	}
}
