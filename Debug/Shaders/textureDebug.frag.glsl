#version 330 core

in vec2 texCoords;

uniform sampler2D myTexture;

out vec4 color;

void main()
{
	color = texture(myTexture, texCoords);	
}