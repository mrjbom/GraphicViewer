#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 mvpMatrix;

void main()
{
    vec4 rPos = mvpMatrix * vec4(aPos, 1.0);
    gl_Position = rPos;
}
