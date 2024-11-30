#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aColor;



out vec3 Norm;
out vec3 Pos;
out vec3 Color;


uniform mat4 ViewMatrix;
uniform mat4 ProjMatrix;
uniform mat4 ModelMatrix;


void main(){

    Norm = aNorm;
    Pos = aPos;
    Color = aColor;


    gl_Position = ProjMatrix *  ViewMatrix * ModelMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);

}