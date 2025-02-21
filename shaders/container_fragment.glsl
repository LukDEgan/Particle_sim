#version 330 core

in vec3 fragmentVertexNormal;
in vec2 fragmentTexCoord;

out vec4 color;

void main()
{
    // Set the container color (white) with transparency
    color = vec4(1.0, 1.0, 1.0, 0.3); // Adjust alpha for transparency
}
