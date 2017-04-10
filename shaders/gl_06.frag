#version 330 core

in vec2 oTexCoord;
in vec3 oPosition;

out vec4 color;

uniform sampler2D Texture0;
uniform sampler2D Texture1;

void main()
{
    vec4 t = texture(Texture1, oTexCoord);
    color = vec4(mix(t.rgb, oPosition, 0.8), 1.0f);
}
