#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aColor;



out vec3 vNorm;
out vec3 vPos;
out vec3 vColor;
out vec4 lightSpacePosition;


uniform mat4 ViewMatrix;
uniform mat4 ProjMatrix;
uniform mat4 ModelMatrix;
uniform mat4 LightSpaceViewMatrix;



void main(){



    vec4 WorldPos = ModelMatrix * vec4(aPos, 1.0);


    vPos = WorldPos.xyz;
    vColor = aColor;
    vNorm = transpose(inverse(mat3(ModelMatrix))) * aNorm;
    //vNorm = aNorm;
    lightSpacePosition = LightSpaceViewMatrix * vec4(vPos, 1.0);

    gl_Position = ProjMatrix *  ViewMatrix * WorldPos;


}