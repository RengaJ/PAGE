#version 130

in vec4 in_position;
in vec2 in_tex;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform float time;

out vec2 v_tex;

void main()
{
	gl_Position = (ProjectionMatrix * ViewMatrix * ModelMatrix) * in_position;
	v_tex = in_tex;
}
