#ifndef __PAGE_MESH_H
#define __PAGE_MESH_H

#include "page_vector.h"
#include "page_debug.h"
#include <vector>

namespace PAGE
{
	class Vertex
	{
		public:
			Vertex() { position = Vector3();normal = Vector3(); uv = Vector2(); }
			Vertex( Vector3 pos ) { position = pos; normal = Vector3(); uv = Vector2(); }
			Vertex( Vector3 pos, Vector3 norm ) { position = pos; normal = norm; uv = Vector2(); }
			Vertex( Vector3 pos, Vector3 norm, Vector2 uvs ) { position = pos; normal = norm; uv = uvs; }
			Vertex(const Vertex &vert) { *this = vert; }

			Vertex& operator=(const Vertex &vert)
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
			Mesh() { vertices = std::vector<Vertex>(); triangles = std::vector<int>(); };

			int vert_count () { return vertices.size(); }
			int tris_count () { return triangles.size(); }
			void add_vertex(Vertex &v) { vertices.push_back(v); }
			void add_triangle(Vector3 &triangle)
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
