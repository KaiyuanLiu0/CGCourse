#version 330 core
out vec4 FragColor;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform vec3 viewPos;
uniform Light light;
uniform float shininess;

uniform samplerCube depthMap;
uniform float far_plane;

float ShadowCalculation(vec3 fragPos)
{
    vec3 fragToLight = FragPos - light.position;

    float closestDepth = texture(depthMap, fragToLight).r;
    closestDepth *= far_plane;
    float currentDepth = length(fragToLight);
    float bias = 0.05; // we use a much larger bias since depth is now in [near_plane, far_plane] range
    float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;
    //FragColor = vec4(vec3(closestDepth / far_plane), 1.0);

    return shadow;
}

float Strength()
{
    vec3 dis = FragPos- light.position;
    return (10.0f / (length(dis) * length(dis)) > 1.0f) ? 1.0f : 10.0f / (length(dis) * length(dis));
}

void main()
{
    float rad = Strength();
    float shadow = ShadowCalculation(FragPos);

    // ambient
    vec3 ambient = light.ambient * texture(texture_diffuse1, TexCoords).rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(texture_diffuse1, TexCoords).rgb;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = light.specular * spec * texture(texture_diffuse1, TexCoords).rgb;

    vec3 result = ambient + rad * (1 - shadow) * (diffuse + specular);
    FragColor = vec4(result, 1.0);
}