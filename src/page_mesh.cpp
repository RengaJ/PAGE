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
    weights = std::map<std::string, float>();
}
Vertex::Vertex( Vector4 pos )
{
    position = pos;
    normal = Vector3();
    color = Vector3(1,1,1);
    uv = Vector2();
    weights = std::map<std::string, float>();
}
Vertex::Vertex( Vector4 pos, Vector3 norm )
{
    position = pos;
    normal = norm;
    color = Vector3(1,1,1);
    uv = Vector2();
    weights = std::map<std::string, float>();
}
Vertex::Vertex( Vector4 pos, Vector3 norm, Vector3 color )
{
    position = pos;
    normal = norm;
    this->color = color;
    uv = Vector2();
    weights = std::map<std::string, float>();
}
Vertex::Vertex( Vector4 pos,Vector3 norm,
                Vector3 color, Vector2 uvs )
{
    position = pos;
    normal = norm;
    this->color = color;
    uv = uvs;
    weights = std::map<std::string, float>();
}

Vertex& Vertex::operator=(const Vertex& vert)
{
    if (this == &vert)
        return *this;
    position = vert.position;
    normal = vert.normal;
    color = vert.color;
    uv = vert.uv;
    weights.clear();
    weights = vert.weights;
    return *this;
}

Vertex::~Vertex()
{
}

void Vertex::addWeight(std::string joint_name, float weight)
{
    if (joint_name == "")
        return;
    weights[joint_name] = weight;
}

float Vertex::getWeight(std::string joint_name)
{
    if (weights.find(joint_name) != weights.end())
        return weights[joint_name];
    return -1;
}

void Vertex::removeWeight(std::string joint_name)
{
    if (weights.find(joint_name) != weights.end())
        weights.erase(joint_name);
}

void Vertex::removeAllWeights()
{
    weights.clear();
}

bool Vertex::hasWeight(float weight)
{
    std::map<std::string, float>::iterator itr = weights.begin();
    while (itr != weights.end())
        if (itr->second == weight)
            return true;
    return false;
}

bool Vertex::boundTo(std::string joint_name)
{
    return (weights.find(joint_name) != weights.end());
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

    texture = Texture2D(); // to make sure that this is a "valid" textured object

    animations = std::vector<Animation>();
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
        int count = 0;
        for (std::map<std::string, float>::iterator itr = vertices[i].weights.begin();
				itr != vertices[i].weights.end(); itr++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (itr->first == "joint1")
				{
					v.joints[count] = 0;
					break;
				}
				if (itr->first == "joint2")
				{
					v.joints[count] = 1;
					break;
				}
				if (itr->first == "joint3")
				{
					v.joints[count] = 2;
					break;
				}
			}
			v.weights[count] = itr->second;
			count++;
		}
        vert[i] = v;
    }
}
// add a weight to a single vertex
void Mesh::add_weight_to(int index, std::string name, float weight)
{
	if (index < 0 || index >= vertices.size())
		return;
	vertices[index].addWeight(name,weight);
}
// add a weight to multiple vertices
void Mesh::add_weight_to(int indexes[], int count, std::string name, float weight)
{
	for (int i = 0; i < count; i++)
		add_weight_to(indexes[i],name,weight);
}
// get weight from vertex joint name
float Mesh::get_weight_from(int index, std::string name)
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

void Mesh::add_animation(Animation &animation)
{
	remove_animation(animation.get_name()); // we don't want duplicatly named animations
	animations.push_back(animation);
}
void Mesh::remove_animation(std::string name)
{
	int counter = 0;
	for (int counter = 0; counter < animations.size(); counter++)
		if (animations[counter].get_name() == name)
			break;
	if (animations.size() != 0 && counter != animations.size())
		animations.erase(animations.begin()+counter);
}
Animation& Mesh::get_animation(std::string name)
{
	Animation a_return = Animation("stoopid");
	for (int i = 0; i < animations.size(); i++)
		if (animations[i].get_name() == name)
		{
			std::cout << "Found the correct animation" << std::endl;
			return animations[i];
		}
	return a_return;
}
