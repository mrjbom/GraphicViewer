#version 450 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 aaNormal;
in vec2 aaTexCoord;
in vec3 aaFragPos;

uniform vec3 cameraPosition;
uniform Material material;
uniform Light light;

out vec4 FragColor;

void main()
{
    vec3 normalizedNormal = normalize(aaNormal);

    //Calculate ambient light
    vec3 ambientLight = light.ambient * vec3(texture(material.diffuse, aaTexCoord));

    //Calculate deffuse light
    vec3 deffuseLightDirection = normalize(light.position - aaFragPos);
    float diffuseLightAngleCoef = max(dot(normalizedNormal, deffuseLightDirection), 0.0);
    vec3 diffuseLight = light.diffuse * (diffuseLightAngleCoef * vec3(texture(material.diffuse, aaTexCoord)));

    //Calculate specular light
    vec3 cameraDirection = normalize(cameraPosition - aaFragPos);
    vec3 reflectLightDirection = reflect(-deffuseLightDirection, normalizedNormal);
    float specularLightAngleCoef = pow(max(dot(cameraDirection, reflectLightDirection), 0.0), material.shininess);
    vec3 specularLight = light.specular * (specularLightAngleCoef * vec3(texture(material.specular, aaTexCoord)));

    vec3 resultColor = ambientLight + diffuseLight + specularLight;

    FragColor = vec4(resultColor, 1.0);
}
