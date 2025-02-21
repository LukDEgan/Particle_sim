#version 330 core
in vec3 fragmentPos;
in vec3 fragmentVertexNormal;
in vec2 fragmentTexCoord;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

out vec4 Fragcolor;

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
    vec3 result = (ambient + diffuse) * objectColor;
    Fragcolor = vec4(result, 1.0);
}