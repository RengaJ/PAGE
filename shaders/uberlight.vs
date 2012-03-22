#version 150

in vec4 in_position;
in vec3 in_normal;
in vec2 in_tex;

// NOTE: WCLightPos is only in here for "legacy"
// suport. The Orange Book 2nd Edition erratas page
// notes that WCLightPos should be removed from this
// shader, as it is not being used at all.
uniform vec3 WCLightPos;      // Position of the light in world coordinates
uniform vec4 ViewPosition;    // Position of the camera (in world space)
uniform mat4 WCtoLC;          // World coordinates to light coordinates transform
uniform mat4 WCtoLCit;        // Inverse Transpose of WCtoLC
uniform mat4 MCtoWC;          // Model Coordinates to world coordinates transform
uniform mat4 MCtoWCit;        // Inverse Transpose of MCtoWC

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 NormalMatrix;

out vec3 LCpos;               // Vertex position (in light coordinates)
out vec3 LCnorm;              // Normal (in light coordinates)
out vec3 LCcamera;            // Camera position (in light coordinates)
out vec2 v_tex;

void main()
{
	// Compute the world space position and normal
	vec4 wcPos = MCtoWC * in_position;
	vec3 wcNorm = (MCtoWCit * vec4(in_normal, 0.0)).xyz;

	// Compute the light coordinate system camera and vertex positions,
	// and the normal
	LCcamera = (WCtoLC * ViewPosition).xyz;
	LCpos = (WCtoLC * wcPos).xyz;
    LCnorm = (WCtoLCit * vec4(wcNorm, 0.0)).xyz;
	gl_Position = (ProjectionMatrix * ViewMatrix * ModelMatrix) * in_position;
	v_tex = in_tex;
}
