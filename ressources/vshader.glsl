#version 330

uniform mat4 mvp;
uniform mat4 mv;
uniform mat4 nm;

in vec3 position;
in vec3 color;
in vec3 normal;

out vec3 fColor;

void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp * vec4(position, 1.0 );

    //CM08a-44
    vec3 sp = vec3(mv*vec4(position, 1.0));
    vec3 V = -normalize(sp);
    vec3 unit_normal = normalize(vec3(nm*vec4(normal, 1.0)));

    float ambientStrength = 0.1;
    vec3 lightPos = vec3(0, 0, -5);
    vec3 lightColor = vec3(1.0f,1.0f,1.0f);
    float constantAttenuation = 1.0;
    float linearAttenuation = 0.0;
    float quadraticAttenuation = 0.1;

    //CM08a-46
    vec3 L = lightPos - sp;
    float d = length(L);
    float attenuation = 1.0 / (constantAttenuation + linearAttenuation * d + quadraticAttenuation * d * d);

    L = normalize(L);
    vec3 halfway_vector = normalize(L+V);
    float pf = 0.0; //power factor
    float nDotH;

    float nDotL = max(0.0, dot(unit_normal, L));
    if(nDotL==0)
        pf = 0.0;
    else{
        nDotH = max(0.0, dot(unit_normal, halfway_vector));
        pf = pow(nDotH, 0.1);
    }

    fColor = (nDotL*attenuation+ambientStrength+pf*attenuation)*lightColor*color;
}
