//================================================//
// MAIN.CPP                                       //
//                                                //
// THIS PROGRAM DISPLAYS A PANDA USING THE        //
// UBERLIGHT SHADER.                              //
////////////////////////////////////////////////////
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
#include "page_utility.h"

#define DEBUG 1

// AN EASY WAY TO DO ERROR CHECKING OPTIMIZATION
#ifdef DEBUG
	#define GL_CHECK(M) if(glGetError() != GL_NO_ERROR) Debug::LogError(M);
#else
	#define GL_CHECK(M)
#endif
// Just some colors I wanted to define...
#define WHITE   glm::vec3(1,1,1)
#define BLACK   glm::vec3(0,0,0)
#define RED     glm::vec3(1,0,0)
#define BLUE    glm::vec3(0,0,1)
#define GREEN   glm::vec3(0,1,0)
#define SEAFOAM glm::vec3(0.250980392,0.890196078,0.592156863)

int width = 800;
int height = 450;
int handle = 0;
double currentTime;
double prevTime;
double deltaTime;
double startTime;

//static const double PI = 3.14159265358979323846;

glm::vec3 eyePos = glm::vec3(0,0,15);
glm::vec3 lookAt = glm::vec3(0,0,0);

//FOV, aspect ratio, near, far
glm::mat4 ProjectionMatrix = glm::perspective(60.0f, 16.0f / 9.0f, 0.1f, 100.f);
glm::mat4 ViewMatrix = glm::mat4(1.0f);
glm::mat4 ModelMatrix = glm::mat4(1.0f);
glm::mat4 NormalMatrix = glm::mat4(1.0f);
glm::mat4 rotationMatrix = glm::mat4(1.0f);

glm::mat4 cameraTransform;

GLboolean barnShaping, ambientClamping;

GLfloat sWidth, sHeight, sWidthEdge, sHeightEdge;
GLfloat sRoundness, dNear, dFar, dNearEdge;
GLfloat dFarEdge, surfaceRoughness;

glm::vec3 surfaceWeights, lightColor, lightWeights, surfaceColor;

glm::vec3 WCLightPos = lookAt-eyePos;
glm::vec4 ViewPosition = glm::vec4(lookAt-eyePos, 1);
// [World|Model] Coordinates to [World|Light]Coordinates [inverse transpose]
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

// VERTEX SHADER UNIFORM LOCATION VARIABLES //
GLuint WCLightPosLocation;   // light in wc
GLuint ViewPositionLocation; // camera pos in wc
GLuint WorldToLightLocation; // wc to lc (matrix)
GLuint WorldToLightITLocation; // inverse tranpose of above
GLuint ModelToWorldLocation;  // mc to wc (matrix)
GLuint ModelToWorldITLocation; // inverse transpose of above
// FRAGMENT SHADER UNIFORM LOCATION VARIABLES //
GLuint SurfaceColorLocation;
// Light Parameters
GLuint LightParamLocations[2] = { 0 };
// [0] = Color , [1] = Location
// Surface parameters
GLuint SurfaceParamLocations[3] = { 0 };
// [0] = Weights, [1] = Roughness, [2] = AmbientClamping
// Super ellipse shaping parameters
GLuint SuperEllipseParamLocations[6] = { 0 };
// [0] = BarnShaping, [1] = Width, [2] = Height
// [3] = WidthEdge, [4] = HeightEdge, [5] = Roundness
// Distance shaping parameters
GLuint DistanceParamLocations[4] = { 0 };
// [0] = Near, [1] = Far, [2] = NearEdge, [3] = FarEdge

float PandaRotation = 0;
double LastTime = 0;

const char* TEXTURE_PATH = "./models/";

using namespace std;
using namespace PAGE;

bool parse_egg(const char* filename);
void parse_vertex(ifstream &file);
void parse_triangle(ifstream &file);
void parse_texture(ifstream &file);

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

PAGE::Mesh mesh;
PAGE::Texture2D texture;

bool parse_egg(const char* filename)
{
	std::ifstream file;
	file.open(filename, std::ifstream::in);

	if (!file.is_open())
	{
		PAGE::Debug::LogError("Failed to open egg file correctly.");
		return false;
	}
	char* token; // we will be using strtok() to parse the file
	char line[256];
	bool examine_file = true;
	while (examine_file) // continue until we reach the end (or when we find <Joint>
	{
		// get the next line of text
		file.getline(line, 256);
		token = strtok(line,"<> {}");
		while (token != NULL)
		{
			if (strncmp(token,"CoordinateSystem",16) == 0)
			{
				token = strtok(NULL,"<> {}");
				if (strncmp(token,"Z-Up",4) == 0)
				{
					mesh.set_coordinate_system(Mesh::Z_UP);
					rotationMatrix = glm::rotate(rotationMatrix, (float)(-PI/2.0)*60, glm::vec3(1,0,0));
				}
				else if (strncmp(token,"Z-Up-right",10) == 0)
				{
					mesh.set_coordinate_system(Mesh::Z_UP_RIGHT);
					rotationMatrix = glm::rotate(rotationMatrix, (float)(-PI/2.0)*60, glm::vec3(1,0,0));
				}
				else if (strncmp(token,"Z-Up-left",9) == 0)
				{
					mesh.set_coordinate_system(Mesh::Z_UP_LEFT);
					rotationMatrix = glm::rotate(rotationMatrix,(float)(PI/2.0)*60, glm::vec3(1,0,0));
				}
				else if (strncmp(token,"Y-up",4) == 0)
					mesh.set_coordinate_system(Mesh::Y_UP);
				else if (strncmp(token,"Y-up-right",10) == 0)
					mesh.set_coordinate_system(Mesh::Y_UP_RIGHT);
				else if (strncmp(token,"Y-up-left",9) == 0)
					mesh.set_coordinate_system(Mesh::Y_UP_LEFT);
			}
			else if (strncmp(token,"Texture",7) == 0 && strlen(token) == 7)
				parse_texture(file);
			// if we found Vertex (not VertexPool):
			else if (strncmp(token,"Vertex",6) == 0 && strlen(token) == 6)
				// go into parse_vertex
				parse_vertex(file);
			else if (strncmp(token,"Polygon",7) == 0 && strlen(token) == 7)
				parse_triangle(file);
			else if (strncmp(token,"Joint",5) == 0) // if we have reached the <Joint> tag, we do not care about the rest of the file. So, we break!
				examine_file = false;
				break;
			token = strtok(NULL,"<> {");
		}

		if (file.eof())
			examine_file = false;
	}
	file.close();

	if (file.is_open())
	{
		PAGE::Debug::LogError("Failed to close egg file correctly.");
		return false;
	}

	return true;
}

void parse_vertex(ifstream &file)
{
	PAGE::Vertex v;

	char line[256];
	file.getline(line, 256);

	PAGE::Vector4 position;
	PAGE::Vector3 normals;
	PAGE::Vector2 uv;
	char* token = strtok(line," ");
	for (int i = 0; i < 3; i++)
	{
		position[i] = atof(token) / 100.0f;
		token = strtok(NULL," ");
	}
	position[3] = 1.0f;

/*	glm::vec4 pos = glm::vec4(position[0], position[1], position[2], position[3]);
	pos = rotationMatrix * pos;

	if (mesh.get_coordinate_system() == Mesh::Z_UP)
	{
		position[0] = pos.x;
		position[1] = pos.y;
		position[2] = pos.z;
		position[3] = pos.w;
	}*/
	// now for normals
	file.getline(line,256);
	token = strtok(line,"<> {}");
	token = strtok(NULL,"<> {}");
	for (int i = 0; i < 3; i++)
	{
		normals[i] = atof(token);
		token = strtok(NULL," ");
	}
	// now for uvs
	file.getline(line,256);
	token = strtok(line,"<> {}");
	token = strtok(NULL,"<> {}");
	for (int i = 0; i < 2; i++)
	{
		uv[i] = atof(token);
		token = strtok(NULL," ");
	}

	v.position = position;
	v.normal = normals;
	v.uv = uv;

	mesh.add_vertex(v);
}

void parse_triangle(ifstream &file)
{
	int  index[3];
	char line[256];
	file.getline(line, 256);
	file.getline(line, 256);
	file.getline(line, 256);

	char* token = strtok(line,"<> {}");
	for (int i = 0; i < 3; i++)
	{
		token = strtok(NULL,"<> {}");
		index[i] = atoi(token) - 1;
	}
	mesh.add_triangle(index[0], index[1], index[2]);
}

void parse_texture(ifstream &file)
{
	char* extension;
	char* token;
	char* filename;
	char line[256];
	file.getline(line, 256);
	token = strtok(line,"\"{}<> ");
	filename = (char*)malloc(strlen(token)+strlen(TEXTURE_PATH)+1);
	strncpy(filename,TEXTURE_PATH, strlen(TEXTURE_PATH));
	strncat(filename,token,strlen(token));
	filename[strlen(token)+strlen(TEXTURE_PATH)] = '\0';
	texture.set_filename(filename);
	extension = strtok(token,".");
	extension = strtok(NULL,".");
	if (strncmp(extension,"png",3) == 0)
		texture.set_file_type(Texture2D::PNG);
	else if (strncmp(extension,"jpeg",4) == 0 ||
			 strncmp(extension,"jpg",3) == 0)
		texture.set_file_type(Texture2D::JPEG);
	else if (strncmp(extension,"bmp",3) == 0)
		texture.set_file_type(Texture2D::BMP);
	else if (strncmp(extension,"tga",3) == 0)
		texture.set_file_type(Texture2D::TGA);
	else if (strncmp(extension,"tiff",4) == 0)
		texture.set_file_type(Texture2D::TIFF);
	for (int i = 0; i < 5; i++)
	{
		file.getline(line,256);
		token = strtok(line,"<>{} ");
		token = strtok(NULL,"<>{} ");

		if (strncmp(token,"format",6) == 0)
		{
			// more formats will be supported later
			token = strtok(NULL,"<>{} ");
			if (strncmp(token,"rbga",4) == 0)
				texture.set_format(GL_RGBA);
			else if (strncmp(token,"rgb",3) == 0)
				texture.set_format(GL_RGB);
			// default is GL_RGB
			continue;
		}

		if (strncmp(token,"wrapu",5) == 0)
		{
			token = strtok(NULL,"<>{} ");
			if (strncmp(token,"repeat",6) == 0)
				texture.set_u_wrap(GL_REPEAT);
			else if (strncmp(token,"clamp",5) == 0)
				texture.set_u_wrap(GL_CLAMP);
			continue;
		}
		if (strncmp(token,"wrapv",5) == 0)
		{
			token = strtok(NULL,"<>{} ");
			if (strncmp(token,"repeat",6) == 0)
				texture.set_v_wrap(GL_REPEAT);
			else if (strncmp(token,"clamp",5) == 0)
				texture.set_v_wrap(GL_CLAMP);
			continue;
		}
		if (strncmp(token,"minfilter",9) == 0)
		{
			token = strtok(NULL,"<>{} ");
			if (strncmp(token,"linear_mipmap_linear",20) == 0)
				texture.set_min_filter(GL_LINEAR_MIPMAP_LINEAR);
			else if (strncmp(token,"linear_mipmap_nearest",21) == 0)
				texture.set_min_filter(GL_LINEAR_MIPMAP_NEAREST);
			else if (strncmp(token,"linear",6) == 0)
				texture.set_min_filter(GL_LINEAR);
			else if (strncmp(token,"nearest_mipmap_linear",21) == 0)
				texture.set_min_filter(GL_NEAREST_MIPMAP_LINEAR);
			else if (strncmp(token,"nearest_mipmap_nearest",22) == 0)
				texture.set_min_filter(GL_NEAREST_MIPMAP_NEAREST);
			else if (strncmp(token,"nearest",7) == 0)
				texture.set_min_filter(GL_NEAREST);

			continue;
		}
		if (strncmp(token,"magfilter",9) == 0)
		{
			token = strtok(NULL,"<>{} ");
			if (strncmp(token,"linear_mipmap_linear",20) == 0)
				texture.set_mag_filter(GL_LINEAR_MIPMAP_LINEAR);
			else if (strncmp(token,"linear_mipmap_nearest",21) == 0)
				texture.set_mag_filter(GL_LINEAR_MIPMAP_NEAREST);
			else if (strncmp(token,"linear",6) == 0)
				texture.set_mag_filter(GL_LINEAR);
			else if (strncmp(token,"nearest_mipmap_linear",21) == 0)
				texture.set_mag_filter(GL_NEAREST_MIPMAP_LINEAR);
			else if (strncmp(token,"nearest_mipmap_nearest",22) == 0)
				texture.set_mag_filter(GL_NEAREST_MIPMAP_NEAREST);
			else if (strncmp(token,"nearest",7) == 0)
				texture.set_mag_filter(GL_NEAREST);
			continue;
		}
	}
}

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
	glFrontFace(GL_CCW); GL_CHECK("Front face failed");
    ViewMatrix = glm::lookAt(eyePos, lookAt, glm::vec3(0.0, 1.0, 0.0));

    create_mesh();
    set_default_values();
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
    if (!parse_egg("./models/panda.egg"))
    {
        Debug::Log("Failed.");
        Debug::LogError("Failed to parse model properly. Exiting.");
        exit(EXIT_FAILURE);
    }
    else
    	Debug::Log("Done!");
    shaderId[0] = glCreateProgram(); GL_CHECK("Could not create shader program.");

    shaderId[1] = load_shader("./shaders/uberlight.fs", GraphicsContext::FRAGMENT);
    check_shader(shaderId[1]);
    shaderId[2] = load_shader("./shaders/uberlight.vs", GraphicsContext::VERTEX);
	check_shader(shaderId[2]);
	glAttachShader(shaderId[0], shaderId[1]);
	glAttachShader(shaderId[0], shaderId[2]);
	GL_CHECK("Failed to attach shaders.");

	glBindAttribLocation(shaderId[0], 0, "in_position"); // Position of the vertex
    glBindAttribLocation(shaderId[0], 1, "in_normal");
	glBindAttribLocation(shaderId[0], 2, "in_tex");
    GL_CHECK("Failed to bind attribute locations.");

	glLinkProgram(shaderId[0]); GL_CHECK("Failed to link the shader program.");

    // VERTEX SHADER UNIFORM LOCATION BINDING //
    WCLightPosLocation = glGetUniformLocation(shaderId[0], "WCLightPos");
    GL_CHECK("Could not get the wc light position uniform location.");
    ViewPositionLocation = glGetUniformLocation(shaderId[0], "ViewPosition");
    GL_CHECK("Could not get the camera position uniform location.");
    WorldToLightLocation = glGetUniformLocation(shaderId[0], "WCtoLC");
    GL_CHECK("Could not get the wc to lc uniform location.");
    WorldToLightITLocation = glGetUniformLocation(shaderId[0], "WCtoLCit");
    GL_CHECK("Could not get the it of wc to lc uniform location.");
    ModelToWorldLocation = glGetUniformLocation(shaderId[0], "MCtoWC");
    GL_CHECK("Could not get the mc to wc uniform location.");
    ModelToWorldITLocation = glGetUniformLocation(shaderId[0], "MCtoWCit");
    GL_CHECK("Could not get the it of mc to wc uniform location.");

    ModelMatrixUniformLocation = glGetUniformLocation(shaderId[0], "ModelMatrix");
    ViewMatrixUniformLocation = glGetUniformLocation(shaderId[0], "ViewMatrix");
    ProjectionMatrixUniformLocation = glGetUniformLocation(shaderId[0], "ProjectionMatrix");
    NormalMatrixUniformLocation = glGetUniformLocation(shaderId[0], "Normal Matrix");
    GL_CHECK("Could not get the matrix uniform locations.");
    // FRAGMENT SHADER UNIFORM LOCATION BINDING //
    SurfaceColorLocation = glGetUniformLocation(shaderId[0], "SurfaceColor");
    GL_CHECK("Could not get the surface color uniform location.");
    // Light Parameters
    LightParamLocations[0] = glGetUniformLocation(shaderId[0], "LightColor");
    LightParamLocations[1] = glGetUniformLocation(shaderId[0], "LightWeights");
    GL_CHECK("Could not get the light parameter uniform locations.");
    // Surface parameters
    SurfaceParamLocations[0] = glGetUniformLocation(shaderId[0], "SurfaceWeights");
    SurfaceParamLocations[1] = glGetUniformLocation(shaderId[0], "SurfaceRoughness");
    SurfaceParamLocations[2] = glGetUniformLocation(shaderId[0], "AmbientClamping");
    GL_CHECK("Could not get the surface parameter uniform locations.");
    // Super ellipse shaping parameters
    SuperEllipseParamLocations[0] = glGetUniformLocation(shaderId[0], "BarnShaping");
    SuperEllipseParamLocations[1] = glGetUniformLocation(shaderId[0], "SWidth");
    SuperEllipseParamLocations[2] = glGetUniformLocation(shaderId[0], "SHeight");
    SuperEllipseParamLocations[3] = glGetUniformLocation(shaderId[0], "SWidthEdge");
    SuperEllipseParamLocations[4] = glGetUniformLocation(shaderId[0], "SHeightEdge");
    SuperEllipseParamLocations[5] = glGetUniformLocation(shaderId[0], "SRoundness");
    GL_CHECK("Could not get the super ellipse parameter uniform locations.");
    // Distance shaping parameters
    DistanceParamLocations[0] = glGetUniformLocation(shaderId[0], "DNear");
    DistanceParamLocations[1] = glGetUniformLocation(shaderId[0], "DFar");
    DistanceParamLocations[2] = glGetUniformLocation(shaderId[0], "DNearEdge");
    DistanceParamLocations[3] = glGetUniformLocation(shaderId[0], "DFarEdge");
    GL_CHECK("Could not get the distance shaping parameter uniform locations.");

    Debug::LogLine("Reticulating vertices...");
    Vertex_S vertices[mesh.vert_count()];
    mesh.convert_verts(vertices);
	Debug::Log("Complete.");

	Debug::LogLine("Interpolating Indices...");
	GLuint indices[mesh.tris_count()];
	std::vector<int> triangles = mesh.tris();
	for (int i = 0; i < triangles.size(); i++)
		indices[i] = (GLuint)triangles[i];
	Debug::Log("Complete.");

	glGenVertexArrays(1, &bufferId[0]);	GL_CHECK("Failed to generate the VAO.");
	glBindVertexArray(bufferId[0]); GL_CHECK("Failed to bind the VAO.");

	glEnableVertexAttribArray(0); // position
	glEnableVertexAttribArray(1); // normal
	glEnableVertexAttribArray(2); // uv
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

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)normal_offset);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)uv_offset);
    GL_CHECK("Failed to set VAO attributes.");

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	GL_CHECK("Failed to bind the IBO to the VAO.");

	glBindVertexArray(0); GL_CHECK("Failed to bind vertex array.");

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

    Debug::Log("Mesh Created.");
}

void set_default_values()
{
    barnShaping = GL_FALSE;
    ambientClamping = GL_FALSE;

    sWidth = 50;
    sHeight = 50;
    sWidthEdge = 1;
    sHeightEdge = 1;
    sRoundness = 0.1;

    dNear = .1;
    dFar = 100;
    dNearEdge = .1;
    dFarEdge = 40;

    surfaceRoughness = 5;
    // the color of the light
    lightColor = WHITE;
    // the color of the surface
    surfaceColor = WHITE;

    // how much of the surface color should the shader use
    // to produce the final color
    surfaceWeights = glm::vec3(1.,1.,1.);
    // how much of the light color should the shader use to
    // produce the final color
    lightWeights = glm::vec3(1.,1.,1.);
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

	ModelMatrix = glm::rotate(ModelMatrix, PandaAngle, glm::vec3(0,1,0));
	ModelMatrix = glm::rotate(ModelMatrix, PandaAngle, glm::vec3(1,0,0));

	for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            normalMatrix[i][j] = ModelMatrix[i][j];
    normalMatrix = glm::transpose(glm::inverse(normalMatrix));


    // world in light coordinates == inv(light in world coordinates)
    MCtoWC = ModelMatrix;
    //MCtoWCit = glm::inverse(glm::transpose(MCtoWC));
    MCtoWCit = glm::transpose(glm::inverse(MCtoWC));

    WCtoLC = glm::translate(ModelMatrix, WCLightPos);
    //WCtoLC = ModelMatrix;
//    WCtoLCit = glm::inverse(glm::transpose(WCtoLC));
    WCtoLCit = glm::transpose(glm::inverse(WCtoLC));

	glUseProgram(shaderId[0]);
	GL_CHECK("DRAW: Could not use the shader program.");

    // VERTEX SHADER UNIFORM BINDINGS //
    // Note that WCLightPos is not used in the uberlight shader
    glUniform3fv(WCLightPosLocation, 1, glm::value_ptr(WCLightPos));
    glUniform4fv(ViewPositionLocation, 1, glm::value_ptr(ViewPosition));
    glUniformMatrix4fv(WorldToLightLocation, 1, GL_FALSE, glm::value_ptr(WCtoLC));
    glUniformMatrix4fv(WorldToLightITLocation, 1, GL_FALSE, glm::value_ptr(WCtoLCit));
    glUniformMatrix4fv(ModelToWorldLocation, 1, GL_FALSE, glm::value_ptr(MCtoWC));
    glUniformMatrix4fv(ModelToWorldITLocation, 1, GL_FALSE, glm::value_ptr(MCtoWCit));
    // ORIGINAL MATRIX INPUTS
    glUniformMatrix4fv(ModelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(ModelMatrix));
    glUniformMatrix4fv(ViewMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
    glUniformMatrix4fv(ProjectionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
    glUniformMatrix4fv(NormalMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    GL_CHECK("Could not set the shader uniforms [VERTEX SHADER]")
    // FRAGMENT SHADER UNIFORM BINDINGS //
    // Light Parameters //
    glUniform3fv(LightParamLocations[0], 1, glm::value_ptr(lightColor));
    glUniform3fv(LightParamLocations[1], 1, glm::value_ptr(lightWeights));
    // Surface Parameters //
    glUniform3fv(SurfaceParamLocations[0], 1, glm::value_ptr(surfaceWeights));
    glUniform1f(SurfaceParamLocations[1], surfaceRoughness);
    glUniform1i(SurfaceParamLocations[2], ambientClamping);
    // Super Ellipse Parameters //
    glUniform1i(SuperEllipseParamLocations[0], barnShaping);
    glUniform1f(SuperEllipseParamLocations[1], sWidth);
    glUniform1f(SuperEllipseParamLocations[2], sHeight);
    glUniform1f(SuperEllipseParamLocations[3], sWidthEdge);
    glUniform1f(SuperEllipseParamLocations[4], sHeightEdge);
    glUniform1f(SuperEllipseParamLocations[5], sRoundness);
    // Distance Shaping Parameters //
    glUniform1f(DistanceParamLocations[0], dNear);
    glUniform1f(DistanceParamLocations[1], dFar);
    glUniform1f(DistanceParamLocations[2], dNearEdge);
    glUniform1f(DistanceParamLocations[3], dFarEdge);
    GL_CHECK("DRAW: Could not set the shader uniforms [FRAGMENT SHADER]");

	glBindVertexArray(bufferId[0]);
	GL_CHECK("DRAW: Could not bind the VAO to draw mesh.");

	glDrawElements(GL_TRIANGLES, mesh.tris_count(), GL_UNSIGNED_INT, (GLvoid*)0);
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
