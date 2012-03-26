#version 130

in vec4 in_position;
in vec3 in_normal;
in vec3 joint_index;
in vec3 weights;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

uniform mat4 joints[3];

void main()
{
	int index_0 = int(joint_index.x);
	int index_1 = int(joint_index.y);
	int index_2 = int(joint_index.z);

	float weight_0 = weights.x;
	float weight_1 = weights.y;
	float weight_2 = weights.z;

	vec4 new_position;
	vec4 new_normal;
	if (index_0 != -1)
	{
		new_position = (joints[index_0] * in_position) * weight_0;
		new_normal = (joints[index_0] * vec4(in_normal,0)) * weight_0;
	}
	if (index_1 != -1)
	{
		new_position = new_position + ((joints[index_1] * in_position) * weight_1);
		new_normal = new_normal + ((joints[index_1] * vec4(in_normal,0)) * weight_1);
	}
	if (index_2 != -1)
	{
		new_position = new_position + ((joints[index_2] * in_position) * weight_2);
		new_normal = new_normal + ((joints[index_2] * vec4(in_normal,0)) * weight_2);
	}
	mat4 ubermatrix = (ProjectionMatrix * ViewMatrix * ModelMatrix);
	mat4 mv_matrix = ViewMatrix * ModelMatrix;

    gl_Position = ubermatrix * vec4(new_position.xyz,1);
}
