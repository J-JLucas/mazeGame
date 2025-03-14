#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

uniform mat4 uMVP;

out vec3 vColor;

void main()
{
  // multiply homogenous vector by MVP matrix to convert to screen space
  gl_Position = uMVP * vec4(aPos, 1.0); 
  vColor = aColor;
}
