#version 330 core

in vec3 ourColour;
out vec4 fragColor;

void main()
{
	fragColor = vec4(ourColor, 1.0f);
}
