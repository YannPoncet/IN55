#version 330

in vec3 fColor;
in vec2 TexCoord;
in float doesHaveTexture;

out vec4 fragColor;

uniform sampler2D colorTexture;

void main()
{
    fragColor = vec4( fColor, 1.0 );

    if(doesHaveTexture > 0.5)
        fragColor = texture2D(colorTexture, TexCoord);
}
