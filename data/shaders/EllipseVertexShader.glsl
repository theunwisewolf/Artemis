#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoords;

uniform mat4 pr_matrix = mat4(1.0f);
uniform vec4 input_position;

out vec3 fragColor;
out vec2 fragTexCoords;

void main()
{
	gl_Position = pr_matrix * (vec4(position.x + input_position.x, position.y + input_position.y, position.zw));
	fragColor = color;
	fragTexCoords = texCoords;
}