#version 410

layout(location = 0) in vec3 vertexPosition_modelspace;

// Values that stay constant for the whole mesh.
uniform mat4 depthProj;
uniform mat4 depthView;

uniform mat4 ModelMatrix;

void main(){
    mat4 depthMVP = depthProj * depthView * ModelMatrix;
    gl_Position =  depthMVP * vec4(vertexPosition_modelspace,1);
}
