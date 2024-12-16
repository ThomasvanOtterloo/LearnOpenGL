
#version 330 core // version of GLSL or OpenGL
layout (location = 0) in vec3 aPos; 

layout (location = 1) in vec3 aColor; 

out vec3 ourColor; // output a color to the fragment shader
out vec4 vertexColor; // output of the vertex shader, which is passed to the fragment shader.

uniform float offset; // uniform variable that is the same for all vertices

void main()
{
    //gl_Position = vec4(aPos , 1.0); // see how we directly give a vec3 to vec4's constructor
    gl_Position = vec4(aPos.x * -1, aPos.y * -1, aPos.z * -1 , 1.0); // upside down triangles
    ourColor = aColor; // set ourColor to the input color we got from the vertex data
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
    gl_Position.x += offset; // add the offset to the x position of the vertex
}