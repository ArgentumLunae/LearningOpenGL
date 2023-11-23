#version 330 core

in vec2 texCoord;
in vec3 ourColor;
out vec4 fragColor;

uniform sampler2D	texture1;
uniform sampler2D	texture2;
uniform float		mixValue;

void main()
{
	fragColor = mix(texture(texture1, texCoord), texture(texture2, vec2(1 - texCoord.x, texCoord.y)), mixValue);
	fragColor *= vec4(ourColor, 1.0);
}
