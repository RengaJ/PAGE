#include "page_parser.h"
#include "page_dof.h"
#include "page_debug.h"
#include "page_animation.h"
#include <iostream>
#include <fstream>

#include <vector>

using namespace PAGE;

bool Parser::parse_egg(const char* filename, Mesh* mesh,  GLenum render_type, bool offset)
{
	std::ifstream file;
	file.open(filename, std::ifstream::in);

	if (mesh == NULL)
        mesh = new Mesh(render_type);
    else
        mesh->set_render_type(render_type);
    mesh->use_offset(offset);
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
			{
			    Debug::Log("TEXTURE FOUND");
				Parser::__parse_egg_texture(file,mesh);
			}
			// if we found Vertex (not VertexPool):
			else if (strncmp(token,"Vertex",6) == 0 && strlen(token) == 6)
				// go into parse_vertex
				Parser::__parse_egg_vertex(file,mesh);
			else if (strncmp(token,"Polygon",7) == 0 && strlen(token) == 7)
				Parser::__parse_egg_polygon(file,mesh);
			else if (strncmp(token,"Joint",5) == 0) // if we have reached the <Joint> tag, we do not care about the rest of the file. So, we break!
			{
				token = strtok(NULL, "<> {}"); // this should be [name]
				Parser::__parse_egg_skeleton(token,file,mesh);
            //    examine_file = false;
            //    break;
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

	PAGE::Vector4 position = Vector4();
	PAGE::Vector3 normals = Vector3();
	PAGE::Vector2 uv = Vector2();
	char* token = strtok(line," ");
	for (int i = 0; i < 3; i++)
	{
		position[i] = atof(token);
		token = strtok(NULL," ");
	}
	position[3] = 1.0f;
    v.position = position;
	// now for normals
	file.getline(line,256);
	token = strtok(line,"<> {}");
	token = strtok(NULL,"<> {}");
	for (int i = 0; i < 3; i++)
	{
		normals[i] = atof(token);
		token = strtok(NULL," ");
	}
    v.normal = normals;
	if (mesh->has_texture())
	{
        // now for uvs
        file.getline(line,256);
        token = strtok(line,"<> {}");
        token = strtok(NULL,"<> {}");
        for (int i = 0; i < 2; i++)
        {
            uv[i] = atof(token);
            token = strtok(NULL," ");
        }
        v.uv = uv;
	}

	mesh->add_vertex(v);
}

void Parser::__parse_egg_polygon(std::ifstream &file, Mesh* mesh)
{
    int counter = 0;
	Vector4 index = Vector4();
	char line[256];
	while (true)
	{
        file.getline(line, 256);
        char* token = strtok(line,"<> {}");
        if (strncmp(token,"VertexRef",9) == 0)
        {
            do
            {
                token = strtok(NULL,"<> {}");
                if (strncmp(token,"Ref",3) == 0)
                    break;
                if (mesh->offset())
                    index[counter++] = atoi(token) - 1;
                else
                    index[counter++] = atoi(token);
            } while (strncmp(token,"Ref",3) != 0);
            if (counter == 2)
                mesh->add_line(index.toVector2());
            if (counter == 3)
                mesh->add_triangle(index.toVector3());
            if (counter == 4)
                mesh->add_quad(index);
            break;
        }
	}
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
		file.getline(line,256); // get line of <Matrix4>
		token = strtok(line," \t");
		for (int j = 0; j < 4; j++)
		{
			matrix[(i*4)+j] = atof(token);
			token = strtok(NULL, " \t");
		}
	}

    // Matrix44 automatically converts row-major into column major (got ahead of myself!)
	joint.set_local_matrix(Matrix44(matrix));

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
		if (strncmp(token,"Scalar",5) == 0) // the order of <Scalar> and <Joint> is unknown, so test for both!
            continue;
        file.seekg((int)file.tellg()-(int)file.gcount());
		if (strncmp(token,"VertexRef",9) == 0) // should break on VertexRef
			break;
	}
	if (strncmp(token, "}", 1) == 0) // we have found the end of the joint! (this might happen)
		/* just look at panda.egg:17534 -> this is the end of a joint, but without any VertexRef attributes! */
		return joint;
	while (true)
	{
	    if (token == NULL)
            break;
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
                index[i] = indices[i]-(mesh->offset() ? 1 : 0);
			token = strtok(NULL,"<> {}");
			if (strncmp(token,"membership",10) == 0)
			{
				token = strtok(NULL,"<> {}");
				weight = atof(token);

				mesh->add_weight_to(index,indices.size(),name,weight);
				file.getline(line,256);
			}
            file.getline(line,256);
			file.getline(line,256);
			token = strtok(line, "<> {}");
		}
		else
			break;
	}
	file.getline(line,256);
	return joint;
}

void Parser::parse_egg_animation(const char* filename, char* animation_name, Mesh* mesh)
{
    std::ifstream file;
    file.open(filename, std::ifstream::in);
    Animation animation = Animation(std::string(animation_name));
    if (!file.is_open())
    {
        Debug::LogError("Failed to open animation file properly.");
        return;
    }
    char line[256];
    char* token;
    // coordinate system
    for (int i = 0; i < 5; i++)
    {
        file.getline(line, 256);
        token = strtok(line,"<> {}");
        if (token == NULL)
			continue;
        if (strncmp(token,"CoordinateSystem",16) == 0)
            continue; // this will be handled at a later date (assumes mesh's coordinate system)
    }
    while (!file.eof())
    {
        file.getline(line, 256);
        token = strtok(line,"<> {}\"");
		if (token == NULL)
			continue;
        if (strncmp(token,"Table",5) == 0)
        {
            token = strtok(NULL, "<> {}\"");
            if (token == NULL)  // <Table> {
                continue;
            if (strncmp(token,"skeleton",8) == 0) // <Table> "<skeleton>" {
            {
                while (true)
                {
                    file.getline(line, 256); // <Table> [joint_name] {
                    token = strtok(line,"<> {}");
					if (token == NULL)
						break;
                    if (strncmp(token,"Table",5) != 0) // Probably means we have encountered a }
                        break;
                    token = strtok(NULL,"<> {}");
                    __parse_egg_animation_joint(file, token, &animation, mesh);
                }
            }
            if (token == NULL) // so much token == NULL checking....GAAAAHHHH!!!!!
				continue;
            if (strncmp(token,"morph",5) == 0) // <Table> morph {
                continue;
        }
    }

    mesh->add_animation(animation);
}

void Parser::__parse_egg_animation_joint(std::ifstream &file, const char* joint_name, Animation *anim, Mesh* mesh)
{
    char line[256];
    char* token;

    if (file.eof())
        return;
	anim->add_joint(joint_name);
    file.getline(line,256);
    token = strtok(line, "<> {}");
    if (strncmp(token, "Xfm$Anim_S$", 11) != 0) // we are probably looking at <Xfm$Anim>
        return; // we will not handle this situation
    token = strtok(NULL, "<> {}");
    if (strncmp(token, "xform", 5) != 0) // we did not find <Xfm$Anim_S$> xform {
    {
        Debug::LogError("Invalid Animation File Detected.");
        return; // this is an invalid animation file
    }
    file.getline(line, 256);
    token = strtok(line, "<> {}");
    if (strncmp(token, "Scalar", 6) == 0) // contains fps information
    {
    	token = strtok(NULL, "<> {}");
    	if (strncmp(token,"fps",3) == 0) // add information to Animation object
		{
			token = strtok(NULL, "<> {}");
			anim->set_fps(atoi(token));
		}
    }
    file.getline(line,256);
    token = strtok(line, "<> {}");
    if (strncmp(token, "Char*", 5) == 0)
    {
		token = strtok(NULL, "<> {}");
		if (strncmp(token,"order",5) == 0)
			anim->set_order(strtok(NULL,"<> {}"));
    }
    // here's the fun part!
    while (true) // while (token != "}")
    {
        file.getline(line, 256);
        token = strtok(line, "<> {}");
        if (token == NULL) // token == "}" (most likely)
            break;
		if (strncmp(token, "S$Anim",6) == 0) // we found a DOF
		{
			token = strtok(NULL, "<> {}");
			DOF::Freedom dof = DOF::get_constraint(token[0]);
			/* this will be one of the following:
			    x,y,z, h,p,r, a,b,c, i,j,k, s, t */
			token = strtok(NULL, "<> {}");
			if (token == NULL) // we have the multi-line version of <S$Anim> [a] { <V> { ... } }
			{
				file.getline(line, 256);
				while (true)
				{
					file.getline(line, 256);
					token = strtok(line," ");
					if (strncmp(token,"}",1) == 0)
					{
						file.getline(line, 256); // the second }
						break;
					}
					while (token != NULL)
					{
						// parse float
						anim->get_joint(joint_name)->set_frame(dof, atof(token));
						token = strtok(NULL, " ");
					}
				}
			}
			else if (strncmp(token, "V", 1) == 0)
			{
				float value = atof(strtok(NULL, "<> {}"));
				anim->get_joint(joint_name)->set_frames(dof,value,0);
			}
		}
    }
}
