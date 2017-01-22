#version 330 core
layout (location = 0) in vec4 position;

layout (std140) uniform mats
{
	mat4 projection;
};

uniform mat4 model;

void main()
{
	gl_Position = vec4(position.xy, 0.0f, 1.0f);
}