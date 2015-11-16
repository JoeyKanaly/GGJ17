#version 330 core

layout (location = 0) in vec4 data;

layout (std140) uniform mats
{
	mat4 projection;
};

uniform mat4 model;

out vec2 texCoords;

void main()
{
	gl_Position = projection * model * vec4(data.xy, 0.0f, 1.0f);
	texCoords = vec2(data.z, data.w);
}