#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float zoomTexCoord;

void main()
{
    // Create a new variable for the adjusted texture coordinates
    vec2 zoomedTexCoord = vec2(TexCoord.x, TexCoord.y * zoomTexCoord);

    // Use the new variable in the texture sampling
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, zoomedTexCoord), 0.2);
}

