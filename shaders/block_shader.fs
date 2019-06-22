#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec3 TexCoord;

out vec4 FragColor;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform float shininess;
uniform samplerCube blockTex;
uniform vec3 viewPos;
uniform Light light;

float Strength()
{
    vec3 dis = FragPos- light.position;
    return 10.0f / (dis.x * dis.x + dis.y * dis.y + dis.z * dis.z);
}

void main()
{
    float rad = Strength();

    // ambient
    vec3 ambient = light.ambient;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = rad * light.diffuse * diff;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = rad * light.specular * spec;

	FragColor = vec4(ambient + diffuse + specular, 1.0f) * texture(blockTex, TexCoord);
}