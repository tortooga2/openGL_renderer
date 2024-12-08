#version 410 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;


in vec3 vPos[];
in vec3 vNorm[];
in vec3 vColor[];


out vec3 outPos;
out vec3 outNorm;
out vec3 outColor;


void main(){

    vec3 vector1 = vPos[0] - vPos[1];
    vec3 vector2 = vPos[2] - vPos[1];

    for(int i = 0; i < gl_in.length(); i++)
    {
        outNorm = normalize(cross(vector2, vector1));
        outPos = vPos[i];
        outColor = vColor[i];
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
}