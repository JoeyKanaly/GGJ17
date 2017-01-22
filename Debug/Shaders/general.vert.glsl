#version 330 core
layout (location = 0) in vec4 data;

layout (std140) uniform mats
{
	mat4 projection;
}

uniform mat4 model;

out vec2 UVPosition;

void main()
{
	gl_Positon = projection * model * vec4(data.x, data.y, 0.0f, 1.0f);
	UVPosition = vec2(data.z, 1.0f - data.w);
}