#version 330

in vec3 fColor;
in vec3 fPosition;
in vec3 fNormal;

uniform mat4 mv;

out vec4 fragColor;

vec3 normalizeNormal, normalizeEyeCoord, normalizeLightVec, V, R, ambient, diffuse, specular;
float sIntensity, cosAngle;

vec3 PhongShading()
{
    vec3 LightPosition = vec3(0,0,0);
    vec3 MaterialAmbient = fColor;
    vec3 LightAmbient = vec3(0.1,0.1,0.1);
    vec3 MaterialDiffuse = fColor;
    vec3 LightDiffuse = vec3(1.0,1.0,1.0);
    vec3 MaterialSpecular = fColor;
    vec3 LightSpecular = vec3(1.0,1.0,1.0);
    float MaterialShininess = 255.0;

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
    fragColor = vec4(PhongShading(), 1.0 );
}
