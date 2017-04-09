#version 330 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D Texture0;
uniform sampler2D Texture1;

void main()
{
    //color = vec4(TexCoord, 1.0, 1.0);
    //color = texture2D(Texture1, vec2(1.0, 1.0) - TexCoord);
    color = mix(texture(Texture1, TexCoord), texture(Texture0, TexCoord),0.4);
}
