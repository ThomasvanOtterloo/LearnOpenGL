
#version 330 core // version of GLSL or OpenGL
layout (location = 0) in vec3 aPos; // sets a var for the vertex position 0, meaning the first vertex attribute. Meaning the position of the vertex.

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); // casts vec3 to a vec4 by added the vec.w component to 1.0.
}