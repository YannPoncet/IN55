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
    vec3 unit_normal = normalize(vec3(nm*vec4(normal, 0.0)));

    float ambientStrength = 0.1;
    vec3 lightPos = vec3(1, 0, 1);
    vec3 lightDir = lightPos;
    vec3 lightColor = vec3(1.0f,1.0f,1.0f);

    //CM08a-45
    vec3 halfway_vector = normalize(V+lightDir);
    float pf = 0.0; //power factor
    float nDotH;

    float nDotL = max(0.0, dot(unit_normal, normalize(lightDir)));
    if(nDotL==0)
        lightColor = vec3(1.0, 1.0, 1.0);
    else{
        nDotH = max(0.0, dot(unit_normal, halfway_vector));
        pf = pow(nDotH, 4*0.2);
    }

    mat3 model = mat3(1.0);
    vec3 norm = mat3(transpose(model))*normal;
    float diff =  max(dot(normalize(norm), lightDir), 0.0);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    fColor = (nDotL+ambientStrength+pf)*lightColor*color;
}
