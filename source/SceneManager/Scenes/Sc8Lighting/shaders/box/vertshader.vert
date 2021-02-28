#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec3 aaNormal;
out vec3 aaFragPos;

void main()
{
    mat4 pvmMatrix = projectionMatrix * viewMatrix * modelMatrix;
    vec4 rPos = pvmMatrix * vec4(aPos, 1.0);
    gl_Position = rPos;
    aaNormal = vec3(modelMatrix * vec4(aNormal, 0.0));
}
