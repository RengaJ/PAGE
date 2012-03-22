#version 150

uniform vec3 SurfaceColor;

// Light Parameters
uniform vec3 LightColor;
uniform vec3 LightWeights;

// Surface parameters
uniform vec3 SurfaceWeights;
uniform float SurfaceRoughness;
uniform bool AmbientClamping;

// Super ellipse shaping parameters
uniform bool BarnShaping;
uniform float SWidth;
uniform float SHeight;
uniform float SWidthEdge;
uniform float SHeightEdge;
uniform float SRoundness;

// Distance shaping parameters
uniform float DNear;
uniform float DFar;
uniform float DNearEdge;
uniform float DFarEdge;

uniform sampler2D s_tex;

in vec3 LCpos;
in vec3 LCnorm;
in vec3 LCcamera;

in vec2 v_tex;

out vec4 FragColor;

float superEllipseShape(vec3 pos)
{
	if (!BarnShaping)
		return 1.0;
	else
	{
		vec2 ppos = pos.xy / pos.z;
		vec2 abspos = abs(ppos);

		float w = SWidth;
		float W = SWidth + SWidthEdge;
		float h = SHeight;
		float H = SHeight + SHeightEdge;

		float exp1 = 2.0 / SRoundness;
		float exp2 = -SRoundness / 2.0;

		float inner = w * h * pow(pow(h * abspos.x, exp1) +
		                          pow(w * abspos.y, exp1),exp2);
		float outer = W * H * pow(pow(H * abspos.x, exp1) +
		                          pow(W * abspos.y, exp1),exp2);
	    return 1.0 - smoothstep(inner, outer, 1.0);
	}
}

float distanceShape(vec3 pos)
{
	float depth = abs(pos.z);
	return smoothstep(DNear - DNearEdge, DNear, depth) *
           (1.0 - smoothstep(DFar, DFar + DFarEdge, depth));
}

void main()
{
	vec3 tmpLightColor = LightColor;
	vec3 N = normalize(LCnorm);
	vec3 L = -normalize(LCpos);
	vec3 V = normalize(LCcamera - LCpos);
	vec3 H = normalize(L + V);

	vec3 tmpColor = tmpLightColor;

	float attenuation = 1.0;
	attenuation *= superEllipseShape(LCpos);
	attenuation *= distanceShape(LCpos);

	float ndotl = dot(N, L);
	float ndoth = dot(N, H);

	vec3 litResult;

	litResult[0] = AmbientClamping ? max(ndotl, 0.0) : 1.0;
	litResult[1] = max(ndotl, 0.0);
	litResult[2] = litResult[1] * max(ndoth, 0.0) * SurfaceRoughness;
	litResult *= SurfaceWeights * LightWeights;

	vec3 ambient = tmpLightColor * SurfaceColor * litResult[0];
	vec3 diffuse = tmpColor * SurfaceColor * litResult[1];
	vec3 specular = tmpColor * litResult[2];
	FragColor = texture(s_tex, v_tex) * vec4(attenuation * (ambient + diffuse + specular), 1.0);
}

