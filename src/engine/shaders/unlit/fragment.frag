#version 430 core

in vec2 fragTexCoord;
out vec4 fragColor;
layout(location = 1) uniform sampler2D mainTexture;

void main() {
    vec4 texel = texture(mainTexture, fragTexCoord);
    if (texel.a < 0.1)
        discard;
    fragColor = texel;
};