
#version 330 core // version of GLSL or OpenGL
layout (location = 0) in vec3 aPos; // sets a var for the vertex position 0, meaning the first vertex attribute. Meaning the position of the vertex.
// the 'in' keyword is used to define the input of a vertex shader.

out vec4 vertexColor; // output of the vertex shader, which is passed to the fragment shader.



void main()
{
    gl_Position = vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor

    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
}