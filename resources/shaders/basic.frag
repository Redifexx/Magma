#version 460 core

in vec3 Normal;
in vec2 TexCoords;
in mat3 TBN;

layout (location = 0) out vec4 FragColor;

void main()
{
    // Directional Light
    vec3 lightDirection = vec3(-0.5, -0.5, -0.5);
    vec3 lightColor = vec3(0.8, 0.8, 0.8);

    float diff = max(dot(Normal, -lightDirection), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0) * lightColor;

    vec3 finalLight = diffuse + vec3(0.1, 0.1, 0.1);

    FragColor = vec4(finalLight, 1.0);
}