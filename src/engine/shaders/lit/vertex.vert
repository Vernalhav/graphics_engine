#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 vertexNormal;

out vec3 fragPositionWorld;			// Position of the fragment in world space
out vec3 viewPositionWorld;			// Position of the viewer in world space
out vec3 fragNormalWorld;			// Fragment normal in world space (not normalized)
out vec2 fragTexCoord;				// Fragment's UV texture coordinates

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 viewProjection;
layout(location = 2) uniform vec3 viewPosition;

void main() {
    fragPositionWorld = vec3(model * vec4(position, 1));
    viewPositionWorld = viewPosition;
    fragNormalWorld = vec3(model * vec4(vertexNormal, 0));
    fragTexCoord = texCoord;

    gl_Position = viewProjection * model * vec4(position, 1);
};