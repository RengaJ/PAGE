#include "page_parser.h"
#include "page_debug.h"
#include <iostream>
#include <fstream>

#include <vector>

using namespace PAGE;

bool Parser::parse_egg(const char* filename, Mesh* mesh)
{
	std::ifstream file;
	file.open(filename, std::ifstream::in);

	if (mesh == NULL)
        mesh = new Mesh();

	if (!file.is_open())
	{
		Debug::LogError("Failed to open egg file correctly.");
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
				Parser::__parse_egg_texture(file,mesh);
			// if we found Vertex (not VertexPool):
			else if (strncmp(token,"Vertex",6) == 0 && strlen(token) == 6)
				// go into parse_vertex
				Parser::__parse_egg_vertex(file,mesh);
			else if (strncmp(token,"Polygon",7) == 0 && strlen(token) == 7)
				Parser::__parse_egg_polygon(file,mesh);
			else if (strncmp(token,"Joint",5) == 0) // if we have reached the <Joint> tag, we do not care about the rest of the file. So, we break!
			{
			//	token = strtok(NULL, "<> {}"); // this should be [name]
			//	Parser::__parse_egg_skeleton(token,file,mesh);
                examine_file = false;
                break;
			}
			token = strtok(NULL,"<> {");
		}

		if (file.eof())
			examine_file = false;
	}
	file.close();

	if (file.is_open())
	{
		Debug::LogError("Failed to close egg file correctly.");
		return false;
	}

	return true;
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

	mesh->add_vertex(v);
}

void Parser::__parse_egg_polygon(std::ifstream &file, Mesh* mesh)
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

void Parser::__parse_egg_skeleton(char* name, std::ifstream &file, Mesh* mesh)
{
	mesh->setSkeleton(__parse_egg_joint(name, file, mesh));
}

// Recursive function
Joint Parser::__parse_egg_joint(char* name, std::ifstream &file, Mesh* mesh)
{
	Joint joint = Joint(std::string(name));
	char* token;
	char line[256];
	file.getline(line,256); // Transform
	file.getline(line,256); // Matrix4

	float matrix[16];
	for (int i = 0; i < 4; i++)
	{
		file.getline(line,256); // Get the first line of Matrix4
		token = strtok(line," \t");
		for (int j = 0; j < 4; j++)
		{
			matrix[(i*4)+j] = atof(token);
			token = strtok(NULL, " \t");
		}
	}

	joint.set_bind_matrix(Matrix44(matrix).transpose());

	file.getline(line,256); // } // matrix4
	file.getline(line,256); // } // transform
	// Check for child joints (recursive calls)
	while (true)
	{
		file.getline(line,256);
		token = strtok(line, "<> {");
		if (strncmp(token,"Joint", 5) == 0)
		{
			token = strtok(NULL, "<> {");
			joint.add_child((Parser::__parse_egg_joint(token, file, mesh)));
		}
		else if (strncmp(token,"Scalar",5) == 0) // the order of <Scalar> and <Joint> is unknown, so test for both!
            continue;
		else // should break on VertexRef
			break;
	}
	if (strncmp(token, "}", 1) == 0) // we have found the end of the joint! (this might happen)
		/* just look at panda.egg:17534 -> this is the end of a joint, but without any VertexRef attributes! */
		return joint;
	while (true)
	{
		if (strncmp(token, "VertexRef", 9) == 0) // we have found VertexRef!
		{
			float weight = -1.0f;
			std::vector<int> indices = std::vector<int>();
			while (true)
			{
				file.getline(line, 256);
				token = strtok(line, "<> {}");
				if (strncmp(token,"Scalar",6) == 0)
					break;
				while (token != NULL)
				{
					indices.push_back(atoi(token));
					token = strtok(NULL, "<> {}");
				}
			}
			int index[indices.size()];
			for (int i = 0; i < indices.size(); i++)
				index[i] = indices[i]-1;
			token = strtok(NULL,"<> {}");
			if (strncmp(token,"membership",10) == 0)
			{
				token = strtok(NULL,"<> {}");
				weight = atof(token);

				mesh->add_weight_to(index,indices.size(),name,weight);
				file.getline(line,256);
				file.getline(line,256);
			}
		}
		else
			break;
	}
	Debug::Log(joint.get_name());
	file.getline(line,256);
	return joint;
}

void Parser::__parse_egg_animation(const char* filename, char* animation_name, Mesh* mesh)
{
}
/*
    General Structure:

<Table> {
  <Bundle> bar {
    <Table> "<skeleton>" {
      <Table> joint1 {
        <Xfm$Anim_S$> xform {
          <Scalar> fps { 24 }
          <Char*> order { srpht }
          <S$Anim> r { <V> { 90 } }
          <S$Anim> y { <V> { 4 } }
        }
        <Table> joint2 {
          <Xfm$Anim_S$> xform {
            <Scalar> fps { 24 }
            <Char*> order { srpht }
            <S$Anim> r { // degree of freedom
              <V> {
                -0 -7.38921 -15.6809 -24.5367 -33.6181 -42.5867 -51.104
                -58.8316 -65.4312 -70.5641 -73.8921 -75.0766 -74.0773
                -71.2533 -66.8651 -61.1735 -54.4392 -46.9229 -38.8852
                -30.5868 -22.2884 -14.2506 -6.73431 -0
              }
            }
            <S$Anim> x { <V> { 4 } }
            <S$Anim> y { <V> { -0.10582 } }
          }
          <Table> joint3 {
            <Xfm$Anim_S$> xform {
              <Scalar> fps { 24 }
              <Char*> order { srpht }
              <S$Anim> r { <V> { -90 } }
              <S$Anim> x { <V> { 4 } }
              <S$Anim> y { <V> { 0.106 } }
            }
          }
        }
      }
    }
    <Table> morph {
    }
  }
}
<Table> "<skeleton>" { -> REQUIRED: Indicates that a skeletal animation
                                    is about to be described.

    Each <Table> entry following this first entry is a joint.
        Each joint is self-contained, with NO NESTING involved!

<Xfm$Anim_S$> -> a simplification of the animation matrix values by
    removing the duplicated and non-changing values

<Scalar> fps { [value] } -> represents the speed of the animation

<S$Anim> [value] { <V> { .. } } -> represents a DOF
    [ value ] is the axis of the DOF
    <V> { ... } is the collection of positions that the degree of freedom
                takes during the course of the animation.
        Note that the size of <V> can only be length(contents)*num_frames
    [value] can be one of the following:
        i, j, k --> scale in x, y, or z
        a, b, c --> shear in xy, xz, or yz
        r, p, h --> roll, pitch, heading
        x, y, z --> translation x, y, or z

    or:
        s       --> uniform scale
 */
