#version 150

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

uniform Light {
    vec4 position;
    vec4 ambient;
    vec4 diffuse;
	vec4 specular;
} light;

uniform Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
	float shininess;
} material;

in vec3 in_Position;
in vec3 in_Normal;
in vec2 in_TexCoord;

out vec2 texCoord;
out vec4 ambientColor;
out vec4 diffuseColor;
out vec4 specularColor;
out vec3 normal;
out vec3 lightDirection;
out vec3 halfVector;
out float shininess;

void main(void) {
    vec4 position = modelViewMatrix * vec4( in_Position, 1.0 );
	gl_Position =  projectionMatrix * position;

    mat3 normalMatrix = transpose( inverse( mat3( modelViewMatrix ) ) );

	normal = normalize( normalMatrix * in_Normal );
    lightDirection = normalize( light.position.xyz );

	halfVector = normalize( lightDirection - position.xyz );

    diffuseColor = light.diffuse * material.diffuse;
    ambientColor = light.ambient * material.ambient;
	specularColor = light.specular * material.specular;
	shininess = material.shininess;

    texCoord = in_TexCoord;
}
