#version 130

in vec4 in_position;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
    gl_Position = (ProjectionMatrix * ViewMatrix * ModelMatrix) * in_position;
}
