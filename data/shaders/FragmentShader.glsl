#version 330 core

in vec3 fragColor;
in vec2 fragTexCoords;

uniform sampler2D texture;

out vec4 glFragColor;

void main()
{
	glFragColor = vec4(fragColor, 1.0f);
}