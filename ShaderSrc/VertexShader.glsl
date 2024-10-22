#version 330 core
layout(location = 0) in vec3 aPos; 

out vec3 FragPos;     

uniform mat4 Model;
uniform mat4 CamMatrix;

void main()
{
    FragPos = vec3(Model * vec4(aPos, 1.0));
    gl_Position = CamMatrix * vec4(FragPos, 1.0);
}
