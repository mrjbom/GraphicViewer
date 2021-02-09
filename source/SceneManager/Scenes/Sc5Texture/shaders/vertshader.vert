#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aWallTexCoord;
layout (location = 2) in vec2 aCatTexCoord;

out vec2 wallTexCoord;
out vec2 catTexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    wallTexCoord = aWallTexCoord;
    catTexCoord = aCatTexCoord;
}
