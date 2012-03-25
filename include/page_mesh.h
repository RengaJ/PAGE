#ifndef __PAGE_MESH_H
#define __PAGE_MESH_H

#include "page_vector.h"
#include "page_utility.h"
#include "page_debug.h"
#include "page_joint.h"
#include "page_texture.h"

#include <vector>

namespace PAGE
{
	class Vertex
	{
		public:
            Vertex();
            Vertex( Vector4 pos );
            Vertex( Vector4 pos, Vector3 norm );
            Vertex( Vector4 pos, Vector3 norm, Vector3 color );
			Vertex( Vector4 pos, Vector3 norm, Vector3 color, Vector2 uvs );
			Vertex(const Vertex &vert) { *this = vert; }

			~Vertex();

			Vertex& operator=(const Vertex &vert);

			void addWeight(const char* joint_name, float weight);
			float getWeight(const char* joint_name);
			void removeWeight(const char* joint_name);
			void removeAllWeights();

			bool hasWeight(float weight);
			bool boundTo(const char* joint_name);

			Vector4 position;
			Vector3 normal;
			Vector3 color;
			Vector2 uv;
			float* weights;
			char** joint_names;
	};

	struct Vertex_S
	{
		float position[4];
		float normal[3];
		float color[3];
		float uv[2];
	//	float weights[3];
	//	char* joint_name[3];
	};

	class Mesh
	{
		public:
			enum CoordinateSystem { Y_UP, Y_UP_RIGHT, Y_UP_LEFT, Z_UP, Z_UP_RIGHT, Z_UP_LEFT };
			Mesh(GLenum polygon_type = GL_TRIANGLES);

			int poly_count ();
			int vert_count () { return vertices.size(); }
			int poly_index_count() { return polygons.size(); }
			void add_vertex(Vertex &v) { vertices.push_back(v); }
			void add_triangle(Vector3 triangle);
			void add_triangle(int v1, int v2, int v3);

			void add_quad(Vector4 quad);
			void add_quad(int v1, int v2, int v3, int v4);

			void add_line(Vector2 line);
			void add_line(int v1, int v2);

			void set_render_type(GLenum render_type);
			GLenum get_render_type();

			std::vector<Vertex> verts() { return vertices; }
			std::vector<int> polys() { return polygons; }

			int vert_array_size() { return vertices.size() * sizeof(Vertex)/sizeof(float); }

			void convert_verts(Vertex_S vert[]);

			CoordinateSystem get_coordinate_system() { return coordinateSystem; }
			void set_coordinate_system(CoordinateSystem system) { coordinateSystem = system; }

            // add a weight to a single vertex
			void add_weight_to(int index, const char* name, float weight);
			// add a weight to multiple vertices
			void add_weight_to(int indexes[], int count, const char* name, float weight);
			// get weight from vertex joint name
			float get_weight_from(int index, const char* name);
			// get all weights from index
			std::vector<float> get_all_weights(int index);
			// get all vertices bound to joint
			std::vector<Vertex> get_all_verts(const char* name);
			// get all vertices bound to a joint with weight
			std::vector<Vertex> get_all_verts(float weight);
            // sets the root of the skeleton
            void setSkeleton(Joint joint);

			void set_texture(Texture2D &tex) { texture = tex; }
			Texture2D get_texture() { return texture; }

			bool has_texture();

			void use_offset(bool offset_type);
			bool offset();

		private:
			CoordinateSystem coordinateSystem;
			std::vector<Vertex> vertices;
			std::vector<int> polygons;
			Texture2D texture;
			Joint skeleton;
			GLenum poly_type;
			bool is_offset;
	};
}

#endif
