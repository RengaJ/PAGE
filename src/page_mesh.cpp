#include "page_utility.h"

#include "page_mesh.h"

using namespace PAGE;

Vertex::Vertex()
{
    position = Vector4();
    normal = Vector3();
    color = Vector3(1,1,1);
    uv = Vector2();
    weights = new float[3];
    joint_names = new char*[3];

    for (int i = 0; i < 3; i++)
    {
        weights[i] = -1.0f;
        joint_names = NULL;
    }
}
Vertex::Vertex( Vector4 pos )
{
    position = pos;
    normal = Vector3();
    color = Vector3(1,1,1);
    uv = Vector2();
    weights = new float[3];
    joint_names = new char*[3];

    for (int i = 0; i < 3; i++)
    {
        weights[i] = -1.0f;
        joint_names = NULL;
    }
}
Vertex::Vertex( Vector4 pos, Vector3 norm )
{
    position = pos;
    normal = norm;
    color = Vector3(1,1,1);
    uv = Vector2();
    weights = new float[3];
    joint_names = new char*[3];

    for (int i = 0; i < 3; i++)
    {
        weights[i] = -1.0f;
        joint_names = NULL;
    }
}
Vertex::Vertex( Vector4 pos, Vector3 norm, Vector3 color )
{
    position = pos;
    normal = norm;
    this->color = color;
    uv = Vector2();
    weights = new float[3];
    joint_names = new char*[3];

    for (int i = 0; i < 3; i++)
    {
        weights[i] = -1.0f;
        joint_names = NULL;
    }
}
Vertex::Vertex( Vector4 pos,Vector3 norm,
                Vector3 color, Vector2 uvs )
{
    position = pos;
    normal = norm;
    this->color = color;
    uv = uvs;
    weights = new float[3];
    joint_names = new char*[3];

    for (int i = 0; i < 3; i++)
    {
        weights[i] = -1.0f;
        joint_names[i] = NULL;
    }
}

Vertex& Vertex::operator=(const Vertex& vert)
{
    if (this == &vert)
        return *this;
    position = vert.position;
    normal = vert.normal;
    uv = vert.uv;
    if (joint_names != NULL)
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
    }
    return *this;
}

Vertex::~Vertex()
{
    delete [] joint_names;
    delete [] weights;
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


Mesh::Mesh()
{
    vertices = std::vector<Vertex>();
    triangles = std::vector<int>();
    coordinateSystem = Y_UP;
}

void Mesh::add_triangle(Vector3 &triangle)
{
    triangles.push_back((int)triangle.x);
    triangles.push_back((int)triangle.y);
    triangles.push_back((int)triangle.z);
}

void Mesh::add_triangle(int v1, int v2, int v3)
{
    triangles.push_back(v1);
    triangles.push_back(v2);
    triangles.push_back(v3);
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
