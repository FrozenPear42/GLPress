#version 330 core

in vec2 oTexCoord;
in vec3 oPosition;

out vec4 color;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform float time;

void main()
{
    vec4 t = texture(diffuseMap, oTexCoord);
    color = vec4(mix(vec3(oTexCoord, sin(time)), t.rgb/2.0f, 0.2), 1.0);
}
