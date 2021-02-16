#version 450 core
out vec4 FragColor;
in vec2 wallTexCoord;

uniform sampler2D boxWallTexture;

void main()
{
    FragColor = texture(boxWallTexture, wallTexCoord);
}
