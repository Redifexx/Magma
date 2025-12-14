#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;


layout (location = 0) uniform mat4 u_ViewProjection;
layout (location = 1) uniform mat4 u_Model;       

out vec3 Normal;
out vec2 TexCoords;
out mat3 TBN;

void main()
{
    gl_Position = u_ViewProjection * u_Model * vec4(aPos, 1.0);
    
    // Normals
    mat3 normalMatrix = mat3(transpose(inverse(u_Model)));
    vec3 n = normalize(normalMatrix * aNormal);
    vec3 t = normalize(normalMatrix * aTangent);
    vec3 b = normalize(normalMatrix * aBitangent);
    t = normalize(t - dot(t, n) * n);
    b = cross(n, t);

    TBN = mat3(t, b, n);
    Normal = n;

    // Texture Coordinates
    TexCoords = aTexCoords;
}