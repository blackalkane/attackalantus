#version 330

// From Vertex Shader
uniform sampler2D screen_texture;
in vec2 texout;
in vec2 vpos; // Distance from local origin

// Application data
uniform sampler2D sampler0;
uniform vec3 fcolor;
uniform int light_up;

// Output color
layout(location = 0) out  vec4 color;


void main()
{
	color = texture(screen_texture, texout);

	float radius = distance(vec2(0.0), vpos);
}