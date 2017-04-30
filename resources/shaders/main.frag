#version 400

struct Light {
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
};

in vec2 oTexCoord;
in vec3 oPosition;
in vec3 oNormal;

out vec4 color;

subroutine vec4 lighting();

subroutine uniform lighting lightType;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;
uniform float shiness;
uniform float time;

uniform Light light;

subroutine (lighting)
vec4 directLight() {
    vec3 diffuse = texture2D(diffuseMap, oTexCoord).rgb;
    vec3 normal = oNormal;//normalize(texture2D(normalMap, oTexCoord).rgb);

    vec3 ambient = light.ambient * diffuse;

    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);

    diffuse = light.diffuse * diff * diffuse;

//    vec3 viewDir = normalize(viewPos - FragPos);
//    vec3 reflectDir = reflect(-lightDir, norm);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    return vec4(ambient + diffuse, 1.0f);
}

subroutine (lighting)
vec4 pointLight() {
    return texture2D(diffuseMap, oTexCoord);
}

subroutine (lighting)
vec4 spotLight() {
    return texture2D(diffuseMap, oTexCoord);
}

void main()
{
    //vec4 t = texture(diffuseMap, oTexCoord);
    //float b = max(0, sin(time/1000.0f));
    //color = vec4(mix(vec3(oTexCoord, b), t.rgb/2.0f, 0.2), 1.0);
    //color = vec4(abs(oNormal), 1.0f);
    color = lightType();
}
