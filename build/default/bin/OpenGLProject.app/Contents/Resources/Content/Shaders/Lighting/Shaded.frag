#version 410 core
out vec4 FragColor;

in vec3 vNorm;
in vec3 vPos;
in vec3 vColor;
in vec4 lightSpacePosition;

uniform sampler2D shadowMap;
uniform vec3 lightPos;
uniform vec3 viewPos;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    return shadow;
}



void main()
{
    vec3 lightDir = normalize(lightPos - vPos);

    float lum = dot(vNorm, lightDir);

    //float shadow = 1.0 - ShadowCalculation(lightSpacePosition);
    //FragColor = vec4(vColor, 1.0) * shadow * lum;
    FragColor = vec4(vColor * lum, 1.0);
}