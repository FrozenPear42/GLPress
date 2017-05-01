#version 400

in vec3 oTexCoords;
out vec4 color;

uniform samplerCube skybox;

void main()
{
    color = vec4(oTexCoords,1);
//    color = texture(skybox, oTexCoords);
}