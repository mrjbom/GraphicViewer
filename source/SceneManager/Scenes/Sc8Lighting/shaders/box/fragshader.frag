#version 450 core
in vec3 aaNormal;
in vec3 aaFragPos;

uniform vec3 cameraPosition;
uniform vec3 objectColor;
uniform vec3 ambientLightColor;
uniform float ambientLightCoef;
uniform vec3 deffuseLightPosition;
uniform vec3 deffuseLightColor;
uniform vec3 specularLightColor;
uniform float specularLightCoef;
uniform float specularLightShineCoef;

out vec4 FragColor;

void main()
{
    vec3 normalizedNormal = normalize(aaNormal);

    //Calculate ambient light
    vec3 ambientLight = ambientLightColor * ambientLightCoef;

    //Calculate deffuse light
    vec3 deffuseLightDirection = normalize(deffuseLightPosition - aaFragPos);
    float diffuseLightAngleCoef = max(dot(normalizedNormal, deffuseLightDirection), 0.0);
    vec3 diffuseLight = diffuseLightAngleCoef * deffuseLightColor;

    //Calculate specular light
    vec3 cameraDirection = normalize(cameraPosition - aaFragPos);
    vec3 reflectLightDirection = reflect(-deffuseLightDirection, normalizedNormal);
    float specularLightAngleCoef = pow(max(dot(cameraDirection, reflectLightDirection), 0.0), specularLightShineCoef);
    vec3 specularLight = specularLightCoef * specularLightAngleCoef * specularLightColor;

    vec3 resultColor = (ambientLight + diffuseLight + specularLight) * objectColor;

    FragColor = vec4(resultColor, 1.0);
}
