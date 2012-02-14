#include "page_debug.h"
#include "page_mesh.h"

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

bool parse_egg(const char* filename, PAGE::Mesh* mesh);
PAGE::Vertex parse_vertex(ifstream &file);

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
	char* line;
	while (!file.eof()) // continue until we reach the end (or when we find <Joint>
	{
		// get the next line of text
		file.getline(line, 256);
		token = strtok(line,"<> {");
		while (token != NULL)
		{
			// if we found Vertex (not VertexPool):
			if (strncmp(token,"Vertex",5) == 0 && strnlen(token) == 5)
			{
				// go into parse_vertex
				PAGE::Vertex v = parse_vertex(file);
				mesh->add_vertex(v);
			}
			if (strncmp(token,"Joint",5) == 0) // if we have reached the <Joint> tag, we do not care about the rest of the file. So, we break!
				break;
		}
	}
	PAGE::Debug::Log(mesh->vert_count());
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
	Vertex v;

	char* line;
	file.getline(line, 256);

	PAGE::Vector3 position;
	file >> position;

	v.position = position;

	return v;
}
