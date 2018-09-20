#version 430 core

out vec4 color;

in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos;

uniform sampler2D Texture;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform float specularStrength;
uniform float ambientStrength;

void main()
{
	// Ambient
	vec3 ambient = ambientStrength * lightColor;	
	
	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);	
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;
		
	// Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = specularStrength * spec * lightColor;
	
	// Rim
	float f = 1.0f - dot(norm, viewDir);	// Calculate the rim factor
	f = smoothstep(0.0f, 1.0f, f);	// constrain it to the range 0 to 1;
	f = pow(f, 16);	// Raise it to the rim exponent
	vec3 rim = f * vec3(1.0f, 0.0f, 0.0f) * lightColor;
	
	vec3 result = (ambient + diffuse + specular /*+ rim*/) * objectColor;

	color = texture(Texture, TexCoord) * vec4(result, 1.0f);
}