#version 150

uniform sampler2D diffuseSampler;
uniform sampler2D ambientSampler;

in vec2 texCoord;

in vec4 ambientColor;
in vec4 diffuseColor;

void main() {
    vec4 ambient = texture( ambientSampler, texCoord );
    ambient *= ambientColor;
    if( ambient.xyz == vec3( 0.0, 0.0, 0.0 ) )
        ambient = ambientColor;

    vec4 diffuse = texture( diffuseSampler, texCoord );
    diffuse *= diffuseColor;
    if( diffuse.xyz == vec3( 0.0, 0.0, 0.0 ) )
        diffuse = diffuseColor;

    gl_FragColor = ambient + diffuse;
}
