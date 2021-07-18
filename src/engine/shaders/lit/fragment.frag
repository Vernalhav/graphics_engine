#version 430 core

struct Material {
	float ambient;
	vec3 diffuse;
	vec3 specular;
	float shinyness;	// Exponent of the specular light component calculation
};

struct AmbientLight {
	float intensity;
	vec3 color;
};

struct PointLight {
	vec3 position;
	vec3 color;

	vec3 attenuationCoefficients;	// Constant, linear and quadratic attenuation coefficients (in that order)
};

in vec3 fragPositionWorld;			// Position of the fragment in world space
in vec3 viewPositionWorld;			// Position of the viewer in world space
in vec3 fragNormalWorld;			// Fragment normal in world space (not normalized)
in vec2 fragTexCoord;				// Fragment's UV texture coordinates

out vec4 fragColor;

layout(location = 3) uniform sampler2D mainTexture;
layout(location = 4) uniform AmbientLight ambient;
layout(location = 5) uniform PointLight light;
layout(location = 6) uniform Material material;

vec3 calculatePointLight(PointLight lightSource, vec3 normalDirection, vec3 viewDirection) {
	vec3 intensity = vec3(0);
	vec3 lightDirection = normalize(lightSource.position - fragPositionWorld);

	// Calculate ambient light contribution
	intensity += ambient.intensity * ambient.color;

	// Calculate diffuse light contribution
	float diffuseIntensity = max(dot(lightDirection, normalDirection), 0);
	intensity += diffuseIntensity * material.diffuse * lightSource.color;

	// Calculate specular light contribution
	vec3 halfVector = normalize(lightDirection + viewDirection);
	float specularIntensity = max(pow(dot(viewDirection, halfVector), material.shinyness), 0);
	intensity += specularIntensity * material.specular * lightSource.color;

	// Calculate distance attenuation
	float dist = distance(fragPositionWorld, lightSource.position);
	vec3 distVec = {1, dist, dist * dist};
	float attenuationFactor = 1 / dot(distVec, lightSource.attenuationCoefficients);

	intensity *= attenuationFactor;

	return intensity;
}


void main() {
   vec4 texel = texture(mainTexture, fragTexCoord);
   if (texel.a < 0.1)
		discard;

	vec3 normal = normalize(fragNormalWorld);
	vec3 viewDirection = normalize(viewPositionWorld - fragPositionWorld);
	vec3 lightIntensity = calculatePointLight(light, normal, viewDirection);

	fragColor = clamp(texel * vec4(lightIntensity, 1), 0, 1);
};