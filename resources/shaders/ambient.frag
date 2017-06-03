#version 400

in vec2 oTexCoord;
in vec3 oPosition;
in vec3 oNormal;

uniform vec2 textureDisplacement;
uniform vec4 ambient;
uniform sampler2D diffuse;

out vec4 color;


void main()
{
    color = ambient * texture2D(diffuse, textureDisplacement + oTexCoord);
}
