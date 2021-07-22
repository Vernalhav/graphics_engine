#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
out vec2 fragTexCoord;

layout(location = 0) uniform mat4 matrixMVP;

void main() {
    fragTexCoord = texCoord;
    gl_Position = matrixMVP * vec4(position, 1);
};