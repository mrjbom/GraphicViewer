#version 450 core
in vec3 aaNormal;
in vec2 aaWallTexCoord;
in vec3 aaFragPos;

uniform sampler2D boxWallTexture;
uniform bool useTexture;
uniform vec3 objectColor;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float ambientLightCoef;

out vec4 FragColor;

void main()
{
    vec3 abmbientColor = objectColor * ambientLightCoef;
    vec3 normalizedNormal = normalize(aaNormal);
    vec3 lightDirection = normalize(lightPosition - aaFragPos);
    float diff = max(dot(normalizedNormal, lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 resultColor = (abmbientColor + diffuse) * objectColor;
    FragColor = vec4(resultColor, 1.0);
}
