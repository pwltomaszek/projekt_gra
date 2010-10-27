#version 150

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

uniform Light {
    vec4 position;
    vec4 ambient;
    vec4 diffuse;
} light;

uniform Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
} material;

in vec3 in_Position;
in vec3 in_Normal;
in vec2 in_TexCoord;

out vec2 texCoord;
out vec4 ambientColor;
out vec4 diffuseColor;

void main(void) {
    vec4 position = modelViewMatrix * vec4( in_Position, 1.0 );

    mat3 normalMatrix = mat3( modelViewMatrix[ 0 ][ 0 ], modelViewMatrix[ 0 ][ 1 ], modelViewMatrix[ 0 ][ 2 ],
                              modelViewMatrix[ 1 ][ 0 ], modelViewMatrix[ 1 ][ 1 ], modelViewMatrix[ 1 ][ 2 ],
                              modelViewMatrix[ 2 ][ 0 ], modelViewMatrix[ 2 ][ 1 ], modelViewMatrix[ 2 ][ 2 ] );
    normalMatrix = transpose( inverse( normalMatrix ) );

    vec3 lightDirection = normalize( vec3( light.position.xyz ) - vec4( modelViewMatrix * position ).xyz );
    vec3 normal = normalize( normalMatrix * in_Normal );
    float diffuseIntensity = max( dot( normal, lightDirection ), 0.0 );

    vec4 diffuse = light.diffuse * material.diffuse * diffuseIntensity;
    vec4 ambient = light.ambient * material.ambient;

    gl_Position =  projectionMatrix * position;
    texCoord = in_TexCoord;

    ambientColor = ambient;
    diffuseColor = diffuse;

    //ambientColor = material.ambient;
    //diffuseColor = material.diffuse;
}
