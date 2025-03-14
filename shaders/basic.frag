#version 330 core
in vec3 vColor;
out vec4 FragColor;

void main()
{
    // A simple color for the cube
    FragColor = vec4(vColor, 1.0);
}
