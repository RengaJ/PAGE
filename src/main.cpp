#include "page_debug.h"
#include "page_mesh.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

bool parse_egg(const char* filename, PAGE::Mesh* mesh);
PAGE::Vertex parse_vertex(ifstream &file);
void parse_triangles(ifstream &file, PAGE::Mesh *mesh);

int main(int argc, char* argv[])
{
	PAGE::Mesh mesh; // create a new Mesh object
	PAGE::Debug::Log("Hello World");

	if (parse_egg("./models/panda.egg", &mesh))
		PAGE::Debug::Log("Hooray!");

	return 0;
}

bool parse_egg(const char* filename, PAGE::Mesh* mesh)
{
	std::ifstream file;
	file.open(filename, std::ifstream::in);

	if (!file.is_open())
	{
		PAGE::Debug::LogError("Failed to open egg file correctly.");
		return false;
	}

	// Begin The Parsing
	// Delimiters: <> {
	// Things to look for:
	// VertexPool
	// 		Vertex int float float float
	//		Normal float float float
	//		UV float float
	// Polygon
	//		VertexRef int int int
	// Joint [ end when we see this ]
	char* token; // we will be using strtok() to parse the file
	char line[256];
	bool examine_file = true;
	while (examine_file) // continue until we reach the end (or when we find <Joint>
	{
		// get the next line of text
		file.getline(line, 256);
		token = strtok(line,"<> {");
		while (token != NULL)
		{
			// if we found Vertex (not VertexPool):
			if (strncmp(token,"Vertex",6) == 0 && strlen(token) == 6)
			{
				// go into parse_vertex
				PAGE::Vertex v = parse_vertex(file);
				mesh->add_vertex(v);
			}
			if (strncmp(token,"Polygon",7) == 0 && strlen(token) == 7)
				parse_triangles(file,mesh);
			if (strncmp(token,"Joint",5) == 0) // if we have reached the <Joint> tag, we do not care about the rest of the file. So, we break!
			{
				examine_file = false;
				break;
			}
			token = strtok(NULL,"<> {");
		}

		if (file.eof())
			examine_file = false;
	}
	cout << mesh->vert_count() << endl;
	cout << mesh->tris_count() << endl;
	file.close();

	if (file.is_open())
	{
		PAGE::Debug::LogError("Failed to close egg file correctly.");
		return false;
	}

	return true;
}

PAGE::Vertex parse_vertex(ifstream &file)
{
	PAGE::Vertex v;

	char line[256];
	file.getline(line, 256);

	PAGE::Vector3 position;
	PAGE::Vector3 normals;
	PAGE::Vector2 uv;
	char* token = strtok(line," ");
	for (int i = 0; i < 3; i++)
	{
		position[i] = atof(token);
		token = strtok(NULL," ");
	}
	// now for normals
	file.getline(line,256);
	token = strtok(line,"<> {");
	token = strtok(NULL,"<> {");
	for (int i = 0; i < 3; i++)
	{
		normals[i] = atof(token);
		token = strtok(NULL," ");
	}
	file.getline(line,256);
	token = strtok(line,"<> {");
	token = strtok(NULL,"<> {");
	for (int i = 0; i < 2; i++)
	{
		uv[i] = atof(token);
		token = strtok(NULL," ");
	}

	v.position = position;
	v.normal = normals;
	v.uv = uv;

	return v;
}

void parse_triangles(ifstream &file, PAGE::Mesh *mesh)
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
		index[i] = atoi(token);
	}
	mesh->add_triangle(index[0], index[1], index[2]);
}
