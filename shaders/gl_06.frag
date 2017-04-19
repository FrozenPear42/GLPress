#version 330 core

in vec2 oTexCoord;
in vec3 oPosition;

out vec4 color;

uniform sampler2D Texture0;
uniform sampler2D Texture1;

void main()
{
    vec4 t = texture(Texture1, oTexCoord);
    //color = vec4(mix(t.rgb, oPosition, 0.4), 1.0f);
    color = vec4(mix(vec3(oTexCoord, 1.0), t.rgb/2.0f, 0.2), 1.0);
}
