#version 400

in vec3 oTexCoords;
out vec4 color;

uniform samplerCube skybox;

void main()
{
    color = texture(skybox, oTexCoords);
//    color = mix(texture(skybox, oTexCoords), vec4(oTexCoords, 1.0), 0.3);
}