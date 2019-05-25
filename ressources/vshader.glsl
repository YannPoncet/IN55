#version 330

uniform mat4 mvp;

in vec3 position;
in vec3 color;
in vec3 normal;

out vec3 fColor;

void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp * vec4( position, 1.0 );

    vec3 light = vec3(1.0,-1.0,1.0);
    float diff =  max(dot(normalize(normal), light), 0.0);
    fColor = diff*color;
}
