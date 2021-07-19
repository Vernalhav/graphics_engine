#version 430 core

#define MAX_LIGHTS 32

/*
    IMPORTANT NOTE:
    In order to explicitly align the following structs properly in memory
    and avoid making mistakes when sending/reading buffers, we shall not
    use any vec3 members in our structs. The vec4s that should be treated
    as vec3s have the _3 suffix. Their 4th component should never be used.

    The OpenGL wiki encourages not using vec3s in structs:
    https://www.khronos.org/opengl/wiki/Interface_Block_(GLSL)#Memory_layout
*/

struct Material {
    float ambient;
    vec4 diffuse_3;

    // Exponent of the specular light component calculation
    float shinyness;
    vec4 specular_3;
};

struct AmbientLight {
    float intensity;
    vec4 color_3;
};

struct PointLight {
    vec4 position_3;
    vec4 color_3;                     

    // Constant, linear and quadratic attenuation coefficients (in that order)
    vec4 attenuationCoefficients_3;   
};

in vec3 fragPositionWorld;			// Position of the fragment in world space
in vec3 viewPositionWorld;			// Position of the viewer in world space
in vec3 fragNormalWorld;			// Fragment normal in world space (not normalized)
in vec2 fragTexCoord;				// Fragment's UV texture coordinates

out vec4 fragColor;

layout(location = 3) uniform sampler2D mainTexture;
uniform Material material;

uniform AmbientLight ambient;
uniform layout(std140) PointLightsBlock {
    int nLights;
    PointLight lights[MAX_LIGHTS];
} PointLights;


vec3 calculatePointLight(PointLight lightSource, vec3 normalDirection, vec3 viewDirection) {
    vec3 intensity = vec3(0);
    vec3 lightDirection = normalize(lightSource.position_3.xyz - fragPositionWorld);

    // Calculate diffuse light contribution
    float diffuseIntensity = max(dot(lightDirection, normalDirection), 0);
    intensity += diffuseIntensity * material.diffuse_3.xyz * lightSource.color_3.xyz;

    // Calculate specular light contribution
    vec3 halfVector = normalize(lightDirection + viewDirection);
    float specularIntensity = max(pow(dot(viewDirection, halfVector), material.shinyness), 0);
    intensity += specularIntensity * material.specular_3.xyz * lightSource.color_3.xyz;

    // Calculate distance attenuation
    float dist = distance(fragPositionWorld, lightSource.position_3.xyz);
    vec3 distVec = {1, dist, dist * dist};
    float attenuationFactor = 1 / dot(distVec, lightSource.attenuationCoefficients_3.xyz);
    intensity *= attenuationFactor;

    return intensity;
}

void main() {
    vec4 texel = texture(mainTexture, fragTexCoord);
    if (texel.a < 0.1) discard;

    vec3 normal = normalize(fragNormalWorld);
    vec3 viewDirection = normalize(viewPositionWorld - fragPositionWorld);

    vec3 lightIntensity = vec3(0);
    lightIntensity += ambient.intensity * ambient.color_3.xyz;

    for (int i = 0; i < PointLights.nLights; i++) {
        lightIntensity += calculatePointLight(PointLights.lights[i], normal, viewDirection);
    }

    fragColor = clamp(texel * vec4(lightIntensity, 1), 0, 1);
};