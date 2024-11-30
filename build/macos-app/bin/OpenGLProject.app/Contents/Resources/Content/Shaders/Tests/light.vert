#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;



out vec3 Norm;
out vec3 Pos;


void main(){

    Norm = aNorm;
    Pos = aPos;
    gl_Position = vec4(aPos.xyz, 1.0);


}