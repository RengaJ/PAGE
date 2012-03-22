#include "page_parser.h"
#include "page_debug.h"
#include <iostream>

using namespace PAGE;

void Parser::parse_egg(const char* filename, Mesh* mesh)
{
	std::ifstream file;
	file.open(filename, std::ifstream::in);

	if (mesh == NULL)
        mesh = new Mesh();

	if (!file.is_open())
	{
		Debug::LogError("Failed to open egg file correctly.");
		return;
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
					mesh->set_coordinate_system(Mesh::Z_UP);
				else if (strncmp(token,"Z-Up-right",10) == 0)
					mesh->set_coordinate_system(Mesh::Z_UP_RIGHT);
				else if (strncmp(token,"Z-Up-left",9) == 0)
					mesh->set_coordinate_system(Mesh::Z_UP_LEFT);
				else if (strncmp(token,"Y-up",4) == 0)
					mesh->set_coordinate_system(Mesh::Y_UP);
				else if (strncmp(token,"Y-up-right",10) == 0)
					mesh->set_coordinate_system(Mesh::Y_UP_RIGHT);
				else if (strncmp(token,"Y-up-left",9) == 0)
					mesh->set_coordinate_system(Mesh::Y_UP_LEFT);
			}
			else if (strncmp(token,"Texture",7) == 0 && strlen(token) == 7)
				continue;//Parser::parse_egg_texture(file);
			// if we found Vertex (not VertexPool):
			else if (strncmp(token,"Vertex",6) == 0 && strlen(token) == 6)
				// go into parse_vertex
				continue;//Parser::parse_egg_vertex(file);
			else if (strncmp(token,"Polygon",7) == 0 && strlen(token) == 7)
				Parser::__parse_egg_triangle(file,mesh);
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
		Debug::LogError("Failed to close egg file correctly.");
		return;
	}
}

void Parser::__parse_egg_texture(std::ifstream &file, Mesh* mesh)
{
    Texture2D texture;
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

	mesh->set_texture(texture);
}

void Parser::__parse_egg_vertex(std::ifstream &file, Mesh* mesh)
{
}

void Parser::__parse_egg_triangle(std::ifstream &file, Mesh* mesh)
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
	mesh->add_triangle(index[0], index[1], index[2]);
}

void Parser::__parse_egg_skeleton()
{
}

void Parser::__parse_egg_animation(const char* filename, char* animation_name, Mesh* mesh)
{
}
