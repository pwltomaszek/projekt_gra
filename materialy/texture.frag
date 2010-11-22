#version 150

uniform sampler2D diffuseSampler;
uniform sampler2D ambientSampler;

in vec2 texCoord;

in vec4 ambientColor;
in vec4 diffuseColor;
in vec4 specularColor;
in vec3 normal, lightDirection, halfVector;
in float shininess;

void main() {
    vec4 ambient = texture( ambientSampler, texCoord );
    ambient *= ambientColor;
    if( ambient.xyz == vec3( 0.0, 0.0, 0.0 ) )
        ambient = ambientColor;

    vec4 diffuse = texture( diffuseSampler, texCoord );
    diffuse *= diffuseColor;
    if( diffuse.xyz == vec3( 0.0, 0.0, 0.0 ) )
        diffuse = diffuseColor;

	vec3 normalizedNormal = normalize( normal );
	vec3 normalizedLightDir = normalize( lightDirection );

	float diffuseIntensity = max( dot( normalizedNormal, normalizedLightDir ), 0.0 );

	vec4 finalColor = ambient;

	float NdotHV;
	if( diffuseIntensity > 0.0 ) {
		finalColor += diffuse * diffuseIntensity;
		vec3 normalizedHalfVector = normalize( halfVector );
		NdotHV = max( dot( normal, normalizedHalfVector ), 0.0 );
		finalColor += specularColor * pow( NdotHV, shininess );
	}

    gl_FragColor = finalColor;
}
