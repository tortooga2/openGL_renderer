#version 410 core
out vec4 FragColor;

in vec3 vNorm;
in vec3 vPos;
in vec3 vColor;

uniform vec3 lightPos;


void main()
{
    vec3 lightDir = normalize(vPos - lightPos);
    float lum = dot(vNorm, lightDir);
    FragColor = vec4(vColor * lum, 1.0);
}