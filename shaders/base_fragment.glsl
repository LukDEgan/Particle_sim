#version 330 core
in vec4 FragColor
out vec4 ScreenColor;
void main()
{
ScreenColor = vec4(FragColor, 1.0f);
}