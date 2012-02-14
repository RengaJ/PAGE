//compiled on Mac with cc -o intro intro.c -l glew -l glfw -framework Cocoa -framework OpenGL
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h> //MUST come before GLFW!
#include <GL/glfw.h>

typedef struct
{
	float XYZW[4];
	float RGBA[4];
} Vertex;

int CurrentWidth = 600, CurrentHeight = 600;
double thistime, oldtime, dt, starttime; //not floats!

GLuint
	VertexShaderId,
	FragmentShaderId,
	ProgramId,
	VaoId,
	BufferId,
	IndexBufferId[2],
	ActiveIndexBuffer = 0;

void Initialize(void);
void RenderFunction(void);
void Cleanup(void);
void CreateVBO(void);
void DestroyVBO(void);
void CreateShaders(void);
void DestroyShaders(void);
void game_loop(void);
void checkShader(GLuint);

const GLchar* VertexShader =
{
	"#version 150\n"\

	"in vec4 in_Position;\n"\
    "in vec4 in_Color;\n"\
	"out vec4 ex_Color;\n"\

	"void main(void)\n"\
	"{\n"\
	"	gl_Position = in_Position;\n"\
	"	ex_Color = in_Color;\n"\
	"}\n"
};

const GLchar* FragmentShader =
{
	"#version 150\n"\

	"in vec4 ex_Color;\n"\
	"out vec4 out_Color;\n"\

	"void main(void)\n"\
	"{\n"\
	"	out_Color = ex_Color;\n"\
	"}\n"
};


int main(int argc, char* argv[])
{
	Initialize();

    game_loop();

    Cleanup();

	exit(EXIT_SUCCESS);
}

void Initialize(void)
{
	GLenum GlewInitResult;

	// Initialize GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }

    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);
    glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if( !glfwOpenWindow( CurrentWidth, CurrentHeight, 0,0,0,0, 16,0, GLFW_WINDOW ) )
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    fprintf(stderr, "GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	glewExperimental = GL_TRUE;
    GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult) {
		fprintf(
			stderr,
			"ERROR: %s\n",
			glewGetErrorString(GlewInitResult)
		);
		exit(EXIT_FAILURE);
	}

	fprintf(
		stdout,
		"INFO: OpenGL Version: %s\n",
		glGetString(GL_VERSION)
	);

    fprintf(
		stdout,
		"INFO: GLEW Version: %s\n",
		glewGetString(GLEW_VERSION)
	);

	CreateShaders();
	CreateVBO();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void game_loop(void){
    int playing;
    playing = GL_TRUE;
    while( playing && glfwGetWindowParam( GLFW_OPENED ) )
    {
        glfwEnable(GLFW_STICKY_KEYS);
        // Frame timer
        oldtime = thistime;
        thistime = glfwGetTime();
        dt = thistime - oldtime;

        //Key events
        // Did the user press ESC?
        if( glfwGetKey( GLFW_KEY_ESC ) )
        {
            playing = GL_FALSE;
        }
        if( glfwGetKey( 'T' ) )
    	{
    			ActiveIndexBuffer = (ActiveIndexBuffer == 1 ? 0 : 1);
    			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId[ActiveIndexBuffer]);
		}
        // Display
        RenderFunction();
        glfwSwapBuffers();
    }
}

void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //draw whatever's active (one of the index array buffers)
	if (ActiveIndexBuffer == 0) {
	    //void glDrawElements(	GLenum mode, GLsizei count, GLenum type, const GLvoid * indices);
        //mode: what kind of primitives to render: GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, \
        GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_QUAD_STRIP, GL_QUADS, and GL_POLYGON
        //count: number of elements (triangles in this case) to render
        //type: type of the values in indices. Must be GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, or GL_UNSIGNED_INT
        //indices: specifies a pointer to the location where the indices are stored. In this case, NULL says \
        to offset 0 bytes into the currently bound GL_ELEMENT_ARRAY_BUFFER and start using the indices from that point
		glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_BYTE, NULL);
	} else {
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, NULL);
	}
}

void Cleanup(void)
{
	DestroyShaders();
	DestroyVBO();
}

void CreateVBO(void)
{
	Vertex Vertices[] =
	{
		{ { 0.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } }, // 0

		// Top
		{ { -0.2f, 0.8f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } }, // 1
		{ { 0.2f, 0.8f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }, // 2
		{ { 0.0f, 0.8f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f } }, //3
		{ { 0.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },	// 4

		// Bottom
		{ { -0.2f, -0.8f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }, // 5
		{ { 0.2f, -0.8f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } }, // 6
		{ { 0.0f, -0.8f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f } }, //7
		{ { 0.0f, -1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },	// 8

		// Left
		{ { -0.8f, -0.2f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } }, // 9
		{ { -0.8f, 0.2f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }, // 10
		{ { -0.8f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f } }, //11
		{ { -1.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },	// 12

		// Right
		{ { 0.8f, -0.2f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }, // 13
		{ { 0.8f, 0.2f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } }, // 14
		{ { 0.8f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f } }, //15
		{ { 1.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } }	// 16
	};

	GLubyte Indices[] = {
		// Top
		0, 1, 3,
		0, 3, 2,
		3, 1, 4,
		3, 4, 2,

		// Bottom
		0, 5, 7,
		0, 7, 6,
		7, 5, 8,
		7, 8, 6,

		// Left
		0, 9, 11,
		0, 11, 10,
		11, 9, 12,
		11, 12, 10,

		// Right
		0, 13, 15,
		0, 15, 14,
		15, 13, 16,
		15, 16, 14
	};

	GLubyte AlternateIndices[] = {
		// Outer square border:
		3, 4, 16,
		3, 15, 16,
		15, 16, 8,
		15, 7, 8,
		7, 8, 12,
		7, 11, 12,
		11, 12, 4,
		11, 3, 4,

		// Inner square
		0, 11, 3,
		0, 3, 15,
		0, 15, 7,
		0, 7, 11
	};

	GLenum ErrorCheckValue = glGetError();
	const size_t BufferSize = sizeof(Vertices);
	const size_t VertexSize = sizeof(Vertices[0]);
	const size_t RgbOffset = sizeof(Vertices[0].XYZW);

    fprintf(stderr, "Buffer Size: %lu, Vertex Size: %lu, RGB Offset: %lu\n",BufferSize, VertexSize, RgbOffset);

	//void glGenBuffers(GLsizei n, GLuint *buffers)
	//Buffer object names are created by calling glGenBuffers. This function creates n handles to buffer \
    objects and stores the names in the array speciï¬ed by BufferId
	glGenBuffers(1, &BufferId);

	//void glBindBuffer(GLenum target, GLuint buffer)
	//A name is activated by calling glBindBuffer. The buffer speciï¬es the name to be bound. \
    The target speciï¬es the binding point, which determines which part of the GL will access \
    the buffer. Several binding points exist, thus just uses a "straight" array of vertices
	glBindBuffer(GL_ARRAY_BUFFER, BufferId);

	//void glBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
	//Note that glBufferData does not take a buffer name has a parameter. Instead it uses the name most recently \
    bound to target
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

    //Create buffers for vertex indices. By specifying '2' to glGenBuffers, we want an array of two buffers
    //the first will be the indices to the cross, the other to the square
	glGenBuffers(2, IndexBufferId);

	//cross indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

    //square indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(AlternateIndices), AlternateIndices, GL_STATIC_DRAW);

    //make the cross active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferId[0]);

	//Create a VAO and make it active
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

    //There are two attributes that we care about for the vertices in this example, position and color
    //void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride)
    //The index parameter speciï¬es which vertex shader attribute will receive the data. User-maintained number
    //The size parameter speciï¬es the number of components are in each element of the buffer (4 values for XYZW and RGBA)
    //The type speciï¬es the data type of the components, which is usually a constant-style version of the datatype, \
    for example, GLubyte -> GL_UNSIGNED_BYTE and Glint -> GL_INT
    //Normalized says, if true, whether to "compress" value to [0,1] or [-1,1] (depending on whether type is signed or not)
    //Stride describes the distance, in bytes, from the start of one element to the start of the next
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

    //Once pointers have been set, any attributes that will be used need to be enabled by calling glEnableVertexAttribArray
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//note: if we need to bind attribute names to locations, (if your version of GLSL won't allow the layout \
	qualifier), it has to happen after the program object is created. See CreateShaders()

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not create a VBO: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}

void DestroyVBO(void)
{
	GLenum ErrorCheckValue = glGetError();

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &BufferId);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(2, IndexBufferId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not destroy the VBO: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}

void CreateShaders(void)
{
	GLenum ErrorCheckValue = glGetError();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource takes in a pointer to a pointer, to leave the option of using an array of strings
	//count is number of strings in the array
	//length is is an optional array of integers that specify the lengths of the strings in "string", but \
	we're using C-style NULL-terminated strings
	//void glShaderSource(GLuint shader, GLsize count, const GLchar **string, const GLint *length)
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);
    checkShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);
    checkShader(FragmentShaderId);

	ProgramId = glCreateProgram();
		glAttachShader(ProgramId, VertexShaderId);
		glAttachShader(ProgramId, FragmentShaderId);

	//need the following two lines if shaders won't compile with layout qualifier
	//glBindAttribLocation(ProgramId, 0, "in_Position");
	//glBindAttribLocation(ProgramId, 1, "in_Color");

	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not create the shaders: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}

void DestroyShaders(void)
{
	GLenum ErrorCheckValue = glGetError();

    //"using" 0 makes no program objects active
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not destroy the shaders: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}

void checkShader(GLuint shader)
{
	GLint status;
	//lGetShaderiv gets a particular parameter of the shader
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		int loglen;
		char logbuffer[1000];
		//there's also a corresponding glGetProgramInfoLog function for the linked program object
		glGetShaderInfoLog(shader, sizeof(logbuffer), &loglen, logbuffer);
		fprintf(stderr, "OpenGL Shader Compile Error:\n%.*s", loglen, logbuffer);
	} else {
		int loglen;
		char logbuffer[1000];
		glGetShaderInfoLog(shader, sizeof(logbuffer), &loglen, logbuffer);
		fprintf(stderr, "OpenGL Shader Compile OK:\n%.*s", loglen, logbuffer);
	}
}
