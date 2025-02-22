#version 330 core
in vec3 fragmentPos;
in vec3 fragmentVertexNormal;
in vec2 fragmentTexCoord;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;
uniform float trans;

out vec4 FragColor;

void main()
{
    //ambient lighting
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;

    //diffuse lighting
    vec3 norm = normalize(fragmentVertexNormal);
    vec3 lightDir = normalize(lightPos - fragmentPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    //specular lightings
    float specularStrength = 0.5;
    vec3 viewDirection = normalize(viewPos-fragmentPos);
    vec3 reflectDirection = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    //result
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, trans);
}