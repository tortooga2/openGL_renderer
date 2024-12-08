#version 410 core
out vec4 FragColor;

in vec3 outNorm;
in vec3 outPos;
in vec3 outColor;



uniform float time;

void main(){

    vec3 lightPos = vec3(-10.0, 10.0, 10.0);
    vec3 lightDir = normalize(vec3(0.0, 0.0, 0.0) - lightPos);



    float lum = dot(normalize(lightDir), normalize(outNorm)) * 0.5 + 0.5;

    FragColor = vec4(outColor * lum, 1.0);




}

