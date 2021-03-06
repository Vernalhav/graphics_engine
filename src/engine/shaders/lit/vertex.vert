#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 vertexNormal;

out vec3 fragPositionWorld;			// Position of the fragment in world space
out vec3 fragNormalWorld;			// Fragment normal in world space (not normalized)
out vec2 fragTexCoord;				// Fragment's UV texture coordinates

layout(location = 0) uniform mat4 modelMatrix;
layout(location = 1) uniform mat4 viewProjectionMatrix;

void main() {
    fragPositionWorld = vec3(modelMatrix * vec4(position, 1));
    fragNormalWorld = vec3(modelMatrix * vec4(vertexNormal, 0));
    fragTexCoord = texCoord;

    gl_Position = viewProjectionMatrix * modelMatrix * vec4(position, 1);
};