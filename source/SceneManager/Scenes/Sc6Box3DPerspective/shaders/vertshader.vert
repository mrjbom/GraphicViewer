#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aWallTexCoord;

uniform mat4 replication_matrix;

out vec2 wallTexCoord;

void main()
{
    vec4 rPos = replication_matrix * vec4(aPos, 1.0);
    gl_Position = rPos;
    wallTexCoord = aWallTexCoord;
}
