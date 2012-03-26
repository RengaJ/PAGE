//================================================//
// MAIN.CPP                                       //
//================================================//
#include "page_utility.h"
//"built-in"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
// glew / glfw
#include <GL/glew.h>
#include <GL/glfw.h>
// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// custom
#include "page_graphics.h"
#include "page_debug.h"
#include "page_mesh.h"
#include "page_texture.h"
#include "page_parser.h"

#define DEBUG 1

// AN EASY WAY TO DO ERROR CHECKING OPTIMIZATION
#ifdef DEBUG
	#define GL_CHECK(M) if(glGetError() != GL_NO_ERROR) Debug::LogError(M);
#else
	#define GL_CHECK(M)
#endif
// Just some colors I wanted to define...
#define WHITE       glm::vec3(1.00,1.00,1.00)
#define BLACK       glm::vec3(0.00,0.00,0.00)
#define RED         glm::vec3(1.00,0.00,0.00)
#define BLUE        glm::vec3(0.00,0.00,1.00)
#define GREEN       glm::vec3(0.00,1.00,0.00)
#define LIGHT_GRAY  glm::vec3(0.75,0.75,0.75)
#define DARK_GRAY   glm::vec3(0.25,0.25,0.25)
#define GRAY        glm::vec3(0.50,0.50,0.50)
#define SEAFOAM glm::vec3(0.250980392,0.890196078,0.592156863)

int width = 800;
int height = 450;
int handle = 0;
double currentTime;
double prevTime;
double deltaTime;
double startTime;

glm::vec3 eyePos = glm::vec3(0,0,15);
glm::vec3 lookAt = glm::vec3(0,0,0);

//FOV, aspect ratio, near, far
glm::mat4 ProjectionMatrix = glm::perspective(60.0f, 16.0f / 9.0f, 0.1f, 100.f);
glm::mat4 ViewMatrix = glm::mat4(1.0f);
glm::mat4 ModelMatrix = glm::mat4(1.0f);
glm::mat4 NormalMatrix = glm::mat4(1.0f);
glm::mat4 rotationMatrix = glm::mat4(1.0f);

glm::mat4 cameraTransform;

glm::vec3 color = LIGHT_GRAY;
glm::vec3 WCLightPos = lookAt-eyePos;
glm::vec4 ViewPosition = glm::vec4(lookAt-eyePos, 1);
glm::mat4 WCtoLC, WCtoLCit, MCtoWC, MCtoWCit;

glm::mat3 normalMatrix = glm::mat3(1.0f);


unsigned FrameCount = 0;

GLuint ProjectionMatrixUniformLocation;
GLuint ViewMatrixUniformLocation;
GLuint ModelMatrixUniformLocation;
GLuint NormalMatrixUniformLocation;
GLuint TimeLocation;
GLuint samplerLoc;
GLuint bufferId[3] = { 0 };
GLuint shaderId[3] = { 0 };
GLuint TexId;

GLuint BoneMatrixUniformLocation;
GLuint DiffuseColorUniformLocation;

float PandaRotation = 0;
double LastTime = 0;

using namespace std;
using namespace PAGE;

void init(int, char*[]);
void init_window(void);
void render(void);
void create_mesh();
void set_default_values();
void render_mesh();
void game_loop(void);
void check_shader(GLuint);
GLuint load_shader(const char*, GraphicsContext::Shader);

void cleanup();
void destroy_shaders();
void destroy_vbos();

PAGE::Mesh mesh = Mesh(GL_TRIANGLES);
PAGE::Texture2D texture;

GLboolean LoadTexture( char* );

int main(int argc, char* argv[])
{
	init(argc, argv);

    game_loop();

    cleanup();

	exit(EXIT_SUCCESS);

	return 0;
}

void init(int argc, char* argv[])
{
	GLenum GlewInitResult;

	init_window(); GL_CHECK("Init Window Failed.");

	glewExperimental = GL_TRUE;
    GlewInitResult = glewInit(); GL_CHECK("GLEW init has some errors.");

	if (GLEW_OK != GlewInitResult) {
		fprintf(
			stderr,
			"ERROR: %s\n",
			glewGetErrorString(GlewInitResult)
		);
		exit(EXIT_FAILURE);
	}
	GL_CHECK("Glew String");

	fprintf(
		stdout,
		"INFO: OpenGL Version: %s\n",
		glGetString(GL_VERSION)
	);
	GL_CHECK("Get String");

    fprintf(
		stdout,
		"INFO: GLEW Version: %s\n",
		glewGetString(GLEW_VERSION)
	);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); GL_CHECK("Clear Color failed.");
	glEnable(GL_DEPTH_TEST); GL_CHECK("Depth test failed");
	glDepthFunc(GL_LESS); GL_CHECK("Depth Func failed");
	glEnable(GL_CULL_FACE); GL_CHECK("Enable cull face failed");
	glCullFace(GL_BACK); GL_CHECK("Cull face failed");
	//glFrontFace(GL_CCW); GL_CHECK("Front face failed");
	glFrontFace(GL_CW); GL_CHECK("Front face failed");
    ViewMatrix = glm::lookAt(eyePos, lookAt, glm::vec3(0.0, 1.0, 0.0));

    create_mesh();
    //set_default_values();
}

void init_window(void)
{
	// init GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to init GLFW\n" );
        exit( EXIT_FAILURE );
    }

    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);
    glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	if( !glfwOpenWindow( width, height, 0,0,0,0, 16,0, GLFW_WINDOW ) )
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    fprintf(stderr, "GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void game_loop(void)
{
    int playing;
    playing = GL_TRUE;
    while( playing && glfwGetWindowParam( GLFW_OPENED ) )
    {
        glfwEnable(GLFW_STICKY_KEYS);
        // Frame timer
        prevTime = currentTime;
        currentTime = glfwGetTime();
        deltaTime = currentTime - prevTime;

        //Key events
        // Did the user press ESC?
        if( glfwGetKey( GLFW_KEY_ESC ) )
        {
            playing = GL_FALSE;
        }

        // Display
        render();
        glfwSwapBuffers();
        glfwDisable(GLFW_STICKY_KEYS);
    }
}

void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	render_mesh();
}

void create_mesh()
{
    Debug::LogLine("Parsing Model...");
    if (!Parser::parse_egg("./models/bendy_bar.egg",&mesh, GL_QUADS, false))
    {
        Debug::Log("Failed.");
        Debug::LogError("Failed to parse model properly. Exiting.");
        exit(EXIT_FAILURE);
    }
    else
    	Debug::Log("Done!");
    texture = mesh.get_texture();

    Debug::Log("Parsing Animation bend");
    Parser::parse_egg_animation("./animations/bendy_bar-bend.egg","bend",&mesh);
    std::cout << "bend Information:\n" << mesh.get_animation("bend") << std::endl;

    shaderId[0] = glCreateProgram(); GL_CHECK("Could not create shader program.");

    shaderId[1] = load_shader("./shaders/diffuse.fs", GraphicsContext::FRAGMENT);
    check_shader(shaderId[1]);
    shaderId[2] = load_shader("./shaders/diffuse.vs", GraphicsContext::VERTEX);
	check_shader(shaderId[2]);
	glAttachShader(shaderId[0], shaderId[1]);
	glAttachShader(shaderId[0], shaderId[2]);
	GL_CHECK("Failed to attach shaders.");

	glBindAttribLocation(shaderId[0], 0, "in_position"); // Position of the vertex
	glBindAttribLocation(shaderId[0], 1, "in_normal");
	glBindAttribLocation(shaderId[0], 2, "joint_index");
	glBindAttribLocation(shaderId[0], 3, "weights");
    GL_CHECK("Failed to bind attribute locations.");

	glLinkProgram(shaderId[0]); GL_CHECK("Failed to link the shader program.");

    // MATRIX UNIFORM LOCATIONS
    ModelMatrixUniformLocation = glGetUniformLocation(shaderId[0], "ModelMatrix");
    ViewMatrixUniformLocation = glGetUniformLocation(shaderId[0], "ViewMatrix");
    ProjectionMatrixUniformLocation = glGetUniformLocation(shaderId[0], "ProjectionMatrix");
    GL_CHECK("Could not get the matrix uniform locations.");

	BoneMatrixUniformLocation = glGetUniformLocation(shaderId[0], "joints");
	GL_CHECK("Could not get joints uniform location");
    DiffuseColorUniformLocation = glGetUniformLocation(shaderId[0], "uColor");
    GL_CHECK("Could not get color uniform location.");

    Debug::LogLine("Reticulating Vertices...");
    Vertex_S vertices[mesh.vert_count()];
    mesh.convert_verts(vertices);
	Debug::Log("Complete.");

	Debug::LogLine("Interpolating Indices...");
	GLuint indices[mesh.poly_index_count()];
	std::vector<int> triangles = mesh.polys();
	for (int i = 0; i < triangles.size(); i++)
		indices[i] = (GLuint)triangles[i];
	Debug::Log("Complete.");

	glGenVertexArrays(1, &bufferId[0]);	GL_CHECK("Failed to generate the VAO.");
	glBindVertexArray(bufferId[0]); GL_CHECK("Failed to bind the VAO.");

	glEnableVertexAttribArray(0); // position
	glEnableVertexAttribArray(1); // normal
	glEnableVertexAttribArray(2); // joint
	glEnableVertexAttribArray(3); // weight
	GL_CHECK("Failed to enable vertex attributes.");

	glGenBuffers(2, &bufferId[1]);
	GL_CHECK("Failed to generate buffer objects.");

	glBindBuffer(GL_ARRAY_BUFFER, bufferId[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	GL_CHECK("Failed to bind VBO to the VAO");

    // calculate offsets
    // Vertex_S is:  [position][normal][color][uv]

	int normal_offset = sizeof(vertices[0].position);
	int color_offset = normal_offset + sizeof(vertices[0].normal);
	int uv_offset = color_offset + sizeof(vertices[0].color);
	int joint_offset = uv_offset + sizeof(vertices[0].uv);
	int weight_offset = joint_offset + sizeof(vertices[0].joints);

	std::cout << "About to perform vertex attrib pointer stuff..." << std::endl;

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)normal_offset);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)joint_offset);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)weight_offset);
    GL_CHECK("Failed to set VAO attributes.");

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	GL_CHECK("Failed to bind the IBO to the VAO.");

	glBindVertexArray(0); GL_CHECK("Failed to bind vertex array.");

    if (texture.valid())
    {
        // Generate texture objects
        glGenTextures( 1, &TexId ); GL_CHECK("Failed to generate texture buffer object.");

        // Make texture object active
        glBindTexture( GL_TEXTURE_2D, TexId ); GL_CHECK("Failed to bind texture buffer object.");

        // Set texture parameters
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture.UWrap());
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture.VWrap());
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture.MagFilter());
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture.MinFilter());
        GL_CHECK("Failed to set texture parameters correctly.");

        // Upload texture from file to texture memory, autouses glTexImage2D, needs TGA
        if (!glfwLoadTexture2D( texture.Name(), 0))
            Debug::LogError("Failed to load texture.");
        samplerLoc = glGetUniformLocation(shaderId[0], "s_tex");

        glUniform1i(samplerLoc, 0);

        Debug::Log("Texture Bound");
    }

    Debug::Log("Mesh Created.");
}

void render_mesh()
{
	float PandaAngle;
	double Now = glfwGetTime();

	if (LastTime == 0)
		LastTime = Now;

	PandaRotation += 450.0f * ((float)(Now - LastTime));
	PandaAngle = PandaRotation * (float)(PI/180);

	LastTime = Now;

	ModelMatrix = glm::mat4(1.0f);
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0,0,-2));

	for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            normalMatrix[i][j] = ModelMatrix[i][j];
    normalMatrix = glm::transpose(glm::inverse(normalMatrix));

    std::vector<Matrix44f> joint_matrix;
    mesh.skeleton_to_array(&joint_matrix);

	glUseProgram(shaderId[0]);
	GL_CHECK("DRAW: Could not use the shader program.");

    // ORIGINAL MATRIX INPUTS
    glUniformMatrix4fv(ModelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(ModelMatrix));
    glUniformMatrix4fv(ViewMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
    glUniformMatrix4fv(ProjectionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
    glUniformMatrix4fv(NormalMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    GL_CHECK("Could not set the shader uniforms [VERTEX SHADER]")

    glUniformMatrix4fv(BoneMatrixUniformLocation, 3, GL_FALSE, joint_matrix[0].mat);
    GL_CHECK("Could not set the bone matrix uniform location.")

    glUniform3fv(DiffuseColorUniformLocation, 1, glm::value_ptr(color));
    GL_CHECK("Could not set the shader uniform for Diffuse Color.")

	glBindVertexArray(bufferId[0]);
	GL_CHECK("DRAW: Could not bind the VAO to draw mesh.");

	glDrawElements(GL_LINE_STRIP, mesh.poly_index_count(), GL_UNSIGNED_INT, (GLvoid*)0);
	GL_CHECK("DRAW: Could not draw the mesh.");

	glBindVertexArray(0);
	glUseProgram(0);
}

void check_shader(GLuint shader)
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
GLuint load_shader(const char* filename, GraphicsContext::Shader type)
{
	GLuint shader_id = 0;
	FILE* file;
	long file_size = -1;
	GLchar* glsl_source;

	GLenum shader_type;

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
	if (fseek(file, 0, SEEK_END) != 0)
	{
		Debug::LogError("Failed to seek through shader file.");
		return -1;
		fclose(file);
	}
	file_size = ftell(file); // grab the file size
	if (file_size == -1)
	{
		Debug::LogError(filename);
		Debug::LogError("File size is unknown.");

		fclose(file);

		return -1;
	}
	// assume we got a good file size
	rewind(file);
	glsl_source = (GLchar*)malloc(file_size+1); // allocate new memory for glsl
	if (file_size != (long)fread(glsl_source, sizeof(GLchar), file_size, file)) // read the data
	{
		Debug::LogError("Failed to properly read shader file.");
		free(glsl_source);
		fclose(file);

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
		GL_CHECK("Could not compile shader");
	}

	free(glsl_source);
	fclose(file);

	return shader_id;
}
void cleanup()
{
	destroy_shaders();
	destroy_vbos();
}

void destroy_shaders()
{
	glDetachShader(shaderId[0], shaderId[1]);
	glDetachShader(shaderId[0], shaderId[2]);
	glDeleteShader(shaderId[1]);
	glDeleteShader(shaderId[2]);
	glDeleteProgram(shaderId[0]);
	GL_CHECK("Failed to destroy shaders.");
}

void destroy_vbos()
{
	glDeleteBuffers(2, &bufferId[1]);
	glDeleteVertexArrays(1, &bufferId[0]);
	GL_CHECK("Failed to destroy buffer objects.");
}
