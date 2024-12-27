#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model; // The object's model matrix
uniform mat4 view; // The camera's view matrix
uniform mat4 projection; // The camera's projection matrix

uniform vec3 lightPos;

out vec3 Normal;   // The normal vector of the current vertex (used to calculate how light interacts with the surface)
out vec3 FragPos;  // The world-space position of the current fragment (used for lighting calculations)
out vec3 LightPos;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0); // Transform the vertex from model space to clip space (view space)
    FragPos = vec3(view * model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(view * model))) * aNormal; 
    LightPos = vec3(view * vec4(lightPos, 1.0)); // Transform world-space light position to view-space light position
}