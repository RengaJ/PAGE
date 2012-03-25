#include "page_utility.h"

#include "page_mesh.h"

#include <iostream>
using namespace PAGE;

Vertex::Vertex()
{
    position = Vector4();
    normal = Vector3();
    color = Vector3(1,1,1);
    uv = Vector2();
 /*   weights = new float[3];
    joint_names = new char*[3];

    for (int i = 0; i < 3; i++)
    {
        weights[i] = -1.0f;
        joint_names = NULL;
    }*/
}
Vertex::Vertex( Vector4 pos )
{
    position = pos;
    normal = Vector3();
    color = Vector3(1,1,1);
    uv = Vector2();
 /*   weights = new float[3];
    joint_names = new char*[3];

    for (int i = 0; i < 3; i++)
    {
        weights[i] = -1.0f;
        joint_names = NULL;
    }*/
}
Vertex::Vertex( Vector4 pos, Vector3 norm )
{
    position = pos;
    normal = norm;
    color = Vector3(1,1,1);
    uv = Vector2();
 /*   weights = new float[3];
    joint_names = new char*[3];

    for (int i = 0; i < 3; i++)
    {
        weights[i] = -1.0f;
        joint_names = NULL;
    }*/
}
Vertex::Vertex( Vector4 pos, Vector3 norm, Vector3 color )
{
    position = pos;
    normal = norm;
    this->color = color;
    uv = Vector2();
 /*   weights = new float[3];
    joint_names = new char*[3];

    for (int i = 0; i < 3; i++)
    {
        weights[i] = -1.0f;
        joint_names = NULL;
    }*/
}
Vertex::Vertex( Vector4 pos,Vector3 norm,
                Vector3 color, Vector2 uvs )
{
    position = pos;
    normal = norm;
    this->color = color;
    uv = uvs;
 /*   weights = new float[3];
    joint_names = new char*[3];

    for (int i = 0; i < 3; i++)
    {
        weights[i] = -1.0f;
        joint_names[i] = NULL;
    }*/
}

Vertex& Vertex::operator=(const Vertex& vert)
{
    if (this == &vert)
        return *this;
    position = vert.position;
    normal = vert.normal;
    color = vert.color;
    uv = vert.uv;
/*    if (joint_names != NULL)
    {
        delete [] joint_names;
        joint_names = NULL;
    }
    if (weights != NULL)
    {
        delete [] weights;
        weights = NULL;
    }
    weights = new float[3];
    joint_names = new char*[3];

    for (int i = 0; i < 3; i++)
    {
        weights[i] = vert.weights[i];
        joint_names[i] = (char*)malloc(sizeof(char)*strlen(vert.joint_names[i])+1);
        strncpy(joint_names[i],vert.joint_names[i],strlen(vert.joint_names[i]));
        joint_names[i][strlen(vert.joint_names[i])] = '\0';
    } */
    return *this;
}

Vertex::~Vertex()
{
 /*   if (joint_names != NULL)
    {
        delete [] joint_names;
        joint_names = NULL;
    }
    if (weights != NULL)
    {
        delete [] weights;
        weights = NULL;
    }*/
}

void Vertex::addWeight(const char* joint_name, float weight)
{
    for (int i = 0; i < 3; i++)
    {
        if (joint_names[i] == NULL)
        {
            joint_names[i] = (char*)malloc(sizeof(char)*strlen(joint_name)+1);
            strncpy(joint_names[i], joint_name, strlen(joint_name));
            joint_names[i][strlen(joint_name)] = '\0';
            weights[i] = weight;
            break;

        }
        if (strncmp(joint_names[i],joint_name,strlen(joint_name)) == 0)
        {
            weights[i] = weight;
            break;
        }
    }
}

float Vertex::getWeight(const char* joint_name)
{
    for (int i = 0; i < 3; i++)
    {
        if (joint_names[i] != NULL)
            if (strncmp(joint_names[i], joint_name, strlen(joint_name)) == 0)
                return weights[i];
    }

    return -1.0f;
}

void Vertex::removeWeight(const char* joint_name)
{
    for (int i = 0; i < 3; i++)
    {
        if (joint_names[i] != NULL)
        {
            if (strncmp(joint_names[i],joint_name,strlen(joint_name)) == 0)
            {
                free(joint_names[i]);
                joint_names[i] = NULL;
                weights[i] = -1.0f;
                break;
            }
        }
    }
}

void Vertex::removeAllWeights()
{
    for (int i = 0; i < 3; i++)
    {
        if (joint_names[i] != NULL)
        {
            free(joint_names[i]);
            joint_names[i] = NULL;
            weights[i] = -1;
        }
    }
}

bool Vertex::hasWeight(float weight)
{
    for (int i = 0; i < 3; i++)
        if (weights[i] == weight)
            return true;
    return false;
}

bool Vertex::boundTo(const char* joint_name)
{
    for (int i = 0; i < 3; i++)
        if (joint_names[i] != NULL && strncmp(joint_names[i],joint_name,strlen(joint_name)) == 0)
            return true;
    return false;
}


Mesh::Mesh(GLenum polygon_type)
{
    vertices = std::vector<Vertex>();
    polygons = std::vector<int>();
    coordinateSystem = Y_UP;
    if (polygon_type == GL_LINES || polygon_type == GL_TRIANGLES || polygon_type == GL_QUADS)
        poly_type = polygon_type;
    else
        poly_type = GL_TRIANGLES;

    texture = Texture2D(); // to make sure that this is a "valid" texture object
}

int Mesh::poly_count()
{
    int divisor = 1;
    if (poly_type == GL_LINES)
        divisor = 2;
    else if (poly_type == GL_TRIANGLES)
        divisor = 3;
    else if (poly_type == GL_QUADS)
        divisor = 4;

    return polygons.size() / divisor;
}
void Mesh::add_triangle(Vector3 triangle)
{
    for (int i = 0; i < 3; i++)
        polygons.push_back((int)triangle[i]);
}

void Mesh::add_triangle(int v1, int v2, int v3)
{
    polygons.push_back(v1);
    polygons.push_back(v2);
    polygons.push_back(v3);
}

void Mesh::add_quad(Vector4 quad)
{
    for (int i = 0; i < 4; i++)
        polygons.push_back((int)quad[i]);
}

void Mesh::add_quad(int v1, int v2, int v3, int v4)
{
    polygons.push_back(v1);
    polygons.push_back(v2);
    polygons.push_back(v3);
    polygons.push_back(v4);
}

void Mesh::add_line(Vector2 line)
{
    polygons.push_back((int)line.x);
    polygons.push_back((int)line.y);
}

void Mesh::add_line(int v1, int v2)
{
    polygons.push_back(v1);
    polygons.push_back(v2);
}

void Mesh::set_render_type(GLenum render_type)
{
    if (render_type == GL_LINES || render_type == GL_TRIANGLES || render_type == GL_QUADS)
        poly_type = render_type;
}

GLenum Mesh::get_render_type()
{
    return poly_type;
}

void Mesh::convert_verts(Vertex_S vert[])
{
    int size = vert_array_size();
    for (int i = 0; i < vertices.size(); i++)
    {
        Vertex_S v;
        for (int j = 0; j < 4; j++)
        {
            v.position[j] = vertices[i].position[j];
            if ( j < 3 )
            {
                v.normal[j] = vertices[i].normal[j];
                v.color[j] = vertices[i].color[j];
                if ( j < 2 )
                    v.uv[j] = vertices[i].uv[j];
            }
        }
        vert[i] = v;
    }
}
// add a weight to a single vertex
void Mesh::add_weight_to(int index, const char* name, float weight)
{
	if (index < 0 || index >= vertices.size())
		return;
	vertices[index].addWeight(name,weight);
}
// add a weight to multiple vertices
void Mesh::add_weight_to(int indexes[], int count, const char* name, float weight)
{
	for (int i = 0; i < count; i++)
		add_weight_to(indexes[i],name,weight);
}
// get weight from vertex joint name
float Mesh::get_weight_from(int index, const char* name)
{
	if (index < 0 || index >= vertices.size())
		return -1.0f;
	vertices[index].getWeight(name);
}

void Mesh::setSkeleton(Joint joint)
{
    skeleton = joint;
}

bool Mesh::has_texture()
{
    return texture.valid();
}

void Mesh::use_offset(bool offset_type)
{
    is_offset = offset_type;
}

bool Mesh::offset()
{
    return is_offset;
}
