#version 330 core
out vec4 FragColor;

in vec3 Norm;
in vec3 Pos;

uniform float light;

void main(){

//    vec3 lightPos = vec3(cos(light.x) * 0.1, sin(-0.8) * 0.1, -0.5);
//
//    vec3 Norm_normalized = normalize(Norm);
//    vec3 light_to_surf = normalize(Pos - lightPos);
//
//    light_to_surf = normalize(light_to_surf);
//
//    float lum = dot(Norm_normalized, light_to_surf) * 0.2;
//
//    FragColor = vec4( vec3(0.8, 0.9, 0.05) * lum, 1.0);

    FragColor = vec4(cos(light), 0.1, 0.6, 1.0);

}

