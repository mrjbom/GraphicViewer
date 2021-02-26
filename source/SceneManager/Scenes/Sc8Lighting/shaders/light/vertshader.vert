#version 450 core
layout (location = 0) in vec3 aPos;

uniform mat4 replication_matrix;

void main()
{
    vec4 rPos = replication_matrix * vec4(aPos, 1.0);
    gl_Position = rPos;
}
