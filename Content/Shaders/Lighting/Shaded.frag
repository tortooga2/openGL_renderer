#version 410 core
out vec4 FragColor;

in vec3 vNorm;
in vec3 vPos;
in vec3 vColor;
in vec4 fragLightCoord;

uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

//float PCFShadowCalculation(vec4 fragPosLightSpace)
//{
//    // Perform perspective divide
//    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
//    // Transform to [0,1] range
//    projCoords = projCoords * 0.5 + 0.5;
//
//    // Get current fragment's depth
//    float currentDepth = projCoords.z;
//
//    // Calculate bias based on surface angle
//    vec3 normal = normalize(vNorm);
//    vec3 lightDir = normalize(lightPos - vec3(0.0, 0.0, 0.0));
//    float normalDotLight = dot(normal, lightDir);
//
//    // Increase bias when surface is almost perpendicular to light
//    float bias = max(0.05 * (1.0 - normalDotLight), 0.0025);
//
//
//    // PCF
//    float shadow = 0.0;
//    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
//
//    for(int x = -1; x <= 1; ++x)
//    {
//        for(int y = -1; y <= 1; ++y)
//        {
//            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
//            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
//        }
//    }
//
//    shadow /= 9.0;
//
//    // Handle edge cases
//    if(projCoords.z > 1.0)
//    shadow = 0.0;
//
//    return shadow;
//}

float ShadowCalculation(vec4 FragPosLightSpace, vec3 lightDir, vec3 normal){
    vec3 projCoords = fragLightCoord.xyz / fragLightCoord.w;
    projCoords = projCoords * 0.5 + 0.5;

    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float bias = max(0.0025 * (1.0 - dot(normal, lightDir)), 0.0008);
    //float bias = 0.001;
    float shadow = (currentDepth >= closestDepth + bias)  ? 1.0 : 0.0;

    return shadow;
}



void main()
{
    vec3 color = vColor;
    vec3 normal = normalize(vNorm);
    vec3 lightColor = vec3(1.0, 0.95, 0.85);

    vec3 ambient = lightColor * 0.15;

    vec3 lightDir = normalize(lightPos - vPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - vPos);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;
    // calculate shadow
    float shadow = ShadowCalculation(fragLightCoord, lightDir, normal);
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;

    FragColor = vec4(lighting, 1.0);

}