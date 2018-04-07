#version 330 core

in vec3 fragColor;
in vec2 fragTexCoords;

uniform sampler2D texture;

out vec4 glFragColor;

void main()
{
	float radius = 0.99f;

	float dist = distance(fragTexCoords.xy, vec2(0.0f, 0.0f));
    float delta = fwidth(dist);
    float alpha = smoothstep(radius - delta, radius, dist);

	if(alpha == 1.0f)
	{
		glFragColor = vec4(1.0f, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		glFragColor = vec4(fragColor.x, fragColor.y, fragColor.z, 1.0f - alpha);
	}

    //glFragColor = vec4(1.0f, alpha, alpha, alpha);
	//glFragColor = vec4(alpha, alpha, alpha, 1.0f);
}