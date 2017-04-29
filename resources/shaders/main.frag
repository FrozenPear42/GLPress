#version 330 core

in vec2 oTexCoord;
in vec3 oPosition;
in vec3 oNormal;

out vec4 color;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform float time;

void main()
{
    vec4 t = texture(diffuseMap, oTexCoord);
    float b = max(0, sin(time/1000.0f));
    color = vec4(mix(vec3(oTexCoord, b), t.rgb/2.0f, 0.2), 1.0);
    //color = vec4(abs(oNormal), 1.0f);
}
