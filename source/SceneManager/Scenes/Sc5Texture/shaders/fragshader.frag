#version 450 core
out vec4 FragColor;
in vec2 wallTexCoord;
in vec2 catTexCoord;

uniform float mixValue;

//for texture
uniform sampler2D wallTexture;
uniform sampler2D catTexture;

void main()
{
    FragColor = mix(texture(wallTexture, wallTexCoord), texture(catTexture, catTexCoord), mixValue);
}
