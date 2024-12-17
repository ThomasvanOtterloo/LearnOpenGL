#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // Mirror the x-coordinate of TexCoord for the second texture
    vec2 mirrorTexCoord = vec2(1.0 - TexCoord.x, TexCoord.y);

    // Mix the two textures: first texture uses TexCoord, second uses mirrorTexCoord
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, mirrorTexCoord), 0.2);
}
