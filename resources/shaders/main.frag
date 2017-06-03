#version 400

struct Light {
    vec3 position;
    vec3 direction;

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

subroutine vec3 lighting();
subroutine uniform lighting lightType;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;
uniform float shiness;
uniform float opacity;

uniform Light light;
uniform vec2 textureDisplacement;

vec2 realTextCoord;


subroutine (lighting)
vec3 directLight() {
    vec3 diffuse = texture2D(diffuseMap, realTextCoord).rgb;
    vec3 normal = oNormal;//normalize(texture2D(normalMap, oTexCoord).rgb);

    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);

    diffuse = light.diffuse * diff * diffuse;

    return vec3(diffuse);
}

subroutine (lighting)
vec3 pointLight() {
    float distance = length(light.position - oPosition);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 diffuse = texture2D(diffuseMap, realTextCoord).rgb;
    vec3 normal = oNormal;//normalize(texture2D(normalMap, oTexCoord).rgb);

    vec3 lightDir = normalize(light.position - oPosition);
    float diff = max(dot(normal, lightDir), 0.0);

    diffuse = light.diffuse * diff * diffuse;

    return vec3(attenuation * diffuse);
}

subroutine (lighting)
vec3 spotLight() {

    float distance = length(light.position - oPosition);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 diffuse = texture2D(diffuseMap, realTextCoord).rgb;
    vec3 normal = oNormal;//normalize(texture2D(normalMap, oTexCoord).rgb);

    vec3 lightDir = normalize(light.position - oPosition);
    float diff = max(dot(normal, lightDir), 0.0);

    // Spotlight (soft edges)
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    diffuse = light.diffuse * diff * diffuse;
    diffuse *= intensity;

    return vec3(attenuation * diffuse);

}

void main()
{
    realTextCoord = oTexCoord + textureDisplacement;
    color = vec4(lightType(), opacity);
//    color = vec4(oPosition, 1.0f);
//    color = vec4(oTexCoord, 1.0, 1.0f);
}
