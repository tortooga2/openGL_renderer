#version 410 core
out vec4 FragColor;

in vec3 vNorm;
in vec3 vPos;
in vec3 vColor;

uniform sampler2D depthMap;
uniform vec4 TestColor;

void main()
{
    vec2 uv = gl_FragCoord.xy / (750.0); // Statically set as I know its how I configured. Too Lazy to make this more responsive.
    float n = 1.0;
    float f = 10.0;
    float z = texture(depthMap, uv.xy).r;

    //Tried to see if I could make anyhting pop incase I just can't tell.
    float linearDepth = (2.0 * n * f) / (f + n - (2.0 * z - 1.0) * (f - n));
    float normalizedDepth = (linearDepth - n) / (f - n);

    FragColor = vec4(vec3(z), 1.0);
}