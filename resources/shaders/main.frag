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
    float distance = length(light.position - oPosition);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 diffuse = texture2D(diffuseMap, oTexCoord).rgb;
    vec3 normal = oNormal;//normalize(texture2D(normalMap, oTexCoord).rgb);

    vec3 ambient = light.ambient * diffuse;

    vec3 lightDir = normalize(light.position - oPosition);
    float diff = max(dot(normal, lightDir), 0.0);

    diffuse = light.diffuse * diff * diffuse;

    return vec4(ambient + attenuation * diffuse, 1.0f);
}

subroutine (lighting)
vec4 spotLight() {

    float distance = length(light.position - oPosition);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 diffuse = texture2D(diffuseMap, oTexCoord).rgb;
    vec3 normal = oNormal;//normalize(texture2D(normalMap, oTexCoord).rgb);

    vec3 ambient = light.ambient * diffuse;

    vec3 lightDir = normalize(light.position - oPosition);
    float diff = max(dot(normal, lightDir), 0.0);

    // Spotlight (soft edges)
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    diffuse = light.diffuse * diff * diffuse;
    diffuse *= intensity;

    return vec4(ambient + attenuation * diffuse, 1.0f);

}

void main()
{
    color = lightType();
    //color = vec4(oPosition, 1.0f);
}
