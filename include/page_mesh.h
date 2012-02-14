#ifndef __PAGE_MESH_H
#define __PAGE_MESH_H

#include "page_vector.h"
#include <vector>

namespace PAGE
{
	class Vertex
	{
		public:
			Vertex();
			Vertex( Vector3 pos ) { *this = Vertex(pos,Vector3(0,0,0),Vector2(0,0)); }
			Vertex( Vector3 pos, Vector3 norm ) { *this = Vertex(pos,norm,Vector2(0,0)); }
			Vertex( Vector3 pos, Vector3 norm, Vector2 uv )
			{ position = pos; normal = norm, this->uv = uv; }
			Vertex(const Vertex &vert) { *this = vert; }

			Vertex operator=(const Vertex &vert)
			{
				if (this == &vert)
					return *this;
				position = vert.position;
				normal = vert.normal;
				uv = vert.uv;

				return *this;
			}

			Vector3 position;
			Vector3 normal;
			Vector2 uv;
	};

	class Mesh
	{
		public:
			Mesh() { };

			int vert_count () { return vertices.size(); }
			void add_vertex(Vertex v) { vertices.push_back(v); }
			void add_triangle(Vector3 triangle)
			{
				triangles.push_back(triangle.x);
				triangles.push_back(triangle.y);
				triangles.push_back(triangle.z);
			}
			void add_triangle(int v1, int v2, int v3)
			{
				triangles.push_back(v1);
				triangles.push_back(v2);
				triangles.push_back(v3);
			}

			std::vector<Vertex> verts() { return vertices; }
			std::vector<int> tris() { return triangles; }

		private:
			std::vector<Vertex> vertices;
			std::vector<int> triangles;
	};
}

#endif
