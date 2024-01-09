#version 330 core

in vec2 texCoord;
in vec3 ourColor;
out vec4 fragColor;

uniform sampler2D	texture1;
uniform sampler2D	texture2;
uniform float		mixValue;

void main()
{
	fragColor = texture(texture1, texCoord);
	// fragColor = vec4(ourColor, 1.0);
	// fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0);
}
