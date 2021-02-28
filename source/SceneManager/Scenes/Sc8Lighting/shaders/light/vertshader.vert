#version 450 core
layout (location = 0) in vec3 aPos;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main()
{
    mat4 pvmMatrix = projectionMatrix * viewMatrix * modelMatrix;
    vec4 rPos = pvmMatrix * vec4(aPos, 1.0);
    gl_Position = rPos;
}
