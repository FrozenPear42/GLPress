#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;


out vec2 oTexCoord;
out vec3 oNormal;
out vec3 oPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    oTexCoord = texCoord;
    oPosition = position;
    oNormal = normal;
    gl_Position = projection * view * model * vec4(position, 1.0f);
}