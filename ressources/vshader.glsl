#version 330

uniform mat4 mvp;
uniform mat4 mv;
uniform mat4 nm;

in vec3 position;
in vec3 color;
in vec3 normal;

out vec3 fNormal;
out vec3 fPosition;
out vec3 fColor;

void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp * vec4( position, 1.0 );

    fNormal = mat3(nm)*normal;
    fPosition = vec3(mv*vec4(position,1.0));
    fColor = color;
}
