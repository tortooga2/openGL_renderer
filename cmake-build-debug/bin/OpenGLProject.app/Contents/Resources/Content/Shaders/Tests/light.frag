#version 330 core
out vec4 FragColor;

in vec3 Norm;
in vec3 Pos;


void main(){

    vec3 lightPos = vec3(1.0, -1.0, -0.2);

    vec3 Norm_normalized = normalize(Norm);
    vec3 light_to_surf = normalize(Pos - lightPos);

    light_to_surf = normalize(light_to_surf);

    float lum = dot(Norm_normalized, light_to_surf);

    FragColor = vec4(vec3(lum), 1.0);

}

