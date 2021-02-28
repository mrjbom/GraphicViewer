#version 450 core
in vec3 aaNormal;
in vec3 aaFragPos;

uniform vec3 objectColor;
uniform vec3 ambientLightColor;
uniform float ambientLightCoef;
uniform vec3 deffuseLightPosition;
uniform vec3 deffuseLightColor;

out vec4 FragColor;

void main()
{
    vec3 normalizedNormal = normalize(aaNormal);
    vec3 ambientLight = ambientLightColor * ambientLightCoef;
    vec3 deffuseLightDirection = normalize(deffuseLightPosition - aaFragPos);
    float diffuseLightAngleCoef = max(dot(normalizedNormal, deffuseLightDirection), 0.0);
    vec3 diffuseLight = diffuseLightAngleCoef * deffuseLightColor;
    vec3 resultColor = (ambientLight + diffuseLight) * objectColor;
    FragColor = vec4(resultColor, 1.0);
}
