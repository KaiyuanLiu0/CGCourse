#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform float shininess;
uniform vec3 viewPos;
uniform Light light;
uniform sampler2D planeTexture;

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
    vec3 dis = FragPos - light.position;
    return (5.0f / (length(dis) * length(dis)) > 1.0f) ? 1.0f : 5.0f / (length(dis) * length(dis));
}



void main()
{
    float rad = Strength();
    float shadow = ShadowCalculation(FragPos);

    // ambient
    vec3 ambient = light.ambient;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = light.specular * spec;

	FragColor = vec4(ambient + (1 - shadow) * rad * (diffuse + specular), 1.0f) * texture(planeTexture, TexCoords);
}
