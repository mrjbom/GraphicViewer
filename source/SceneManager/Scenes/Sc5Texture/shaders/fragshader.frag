#version 450 core
out vec4 FragColor;
in vec2 wallTexCoord;
in vec2 catTexCoord;

uniform float mix_value;

//for texture
uniform sampler2D wallTexture;
uniform sampler2D catTexture;

void main()
{
    FragColor = mix(texture(wallTexture, wallTexCoord), texture(catTexture, catTexCoord), mix_value);
}
