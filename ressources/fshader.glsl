#version 330
#define N 5

in vec3 fColor;
in vec3 fPosition;
in vec3 fNormal;

uniform mat4 mv;
uniform int nbLights;
uniform vec3 LightPositions[int(N)];

out vec4 fragColor;

vec3 normalizeNormal, normalizeEyeCoord, normalizeLightVec, V, R, ambient, diffuse, specular;
float sIntensity, cosAngle;

vec3 PhongShading(int i)
{
    vec3 LightPosition = LightPositions[i];
    vec3 MaterialAmbient = fColor;
    vec3 LightAmbient = vec3(0.0,0.0,0.0);
    vec3 MaterialDiffuse = fColor;
    vec3 LightDiffuse = vec3(1.0,1.0,1.0);
    vec3 MaterialSpecular = vec3(0.0,0.0,0.0);
    vec3 LightSpecular = vec3(1.0,1.0,1.0);
    float MaterialShininess = 30.0;

    normalizeNormal = normalize(fNormal);
    normalizeEyeCoord = normalize(fPosition);
    normalizeLightVec = normalize(LightPosition - fPosition);

    // Diffuse Intensity
    cosAngle = max(0.0,
    dot(normalizeNormal,normalizeLightVec));
    // Specular Intensity
    V = -normalizeEyeCoord; // Viewer's vector
    R = reflect(-normalizeLightVec, normalizeNormal);
    sIntensity = pow(max(0.0,dot(R,V)), MaterialShininess);
    ambient = MaterialAmbient * LightAmbient;
    diffuse = MaterialDiffuse * LightDiffuse;
    specular = MaterialSpecular * LightSpecular;

    return ambient+(cosAngle*diffuse)+(sIntensity*specular);
}

void main()
{
    vec4 tmpColor = vec4(0.0);
    for(int i=0; i<nbLights; i++)
        tmpColor += vec4(PhongShading(i), 1.0 );
    fragColor = tmpColor;
}
