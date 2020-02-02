// This is Fragment Shader

#version 330 core
out vec4 FragColor;

in vec3 passColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;

uniform sampler2D outTexture;

void main()
{
	vec3 ambientLight = vec3 (0.5, 0.5, 0.5);
	vec3 ambient = ambientLight * lightColor;

	vec3 normalVector = Normal;
	vec3 lightDir = normalize(lightPos - FragPos);
	float diffuseLight = max(dot(normalVector, lightDir), 0.0);
	vec3 diffuse = diffuseLight * lightColor;
	

	int shininess = 32;
	vec3 viewDir = normalize(FragPos - viewPos);
	vec3 reflectDir = reflect(lightDir, normalVector);
	float specularColor = max(dot(viewDir, reflectDir), 0.0);
	vec3 specular = specularColor * lightColor;
	

	vec3 result = (ambient + diffuse + specular) * texture(outTexture, TexCoord).rgb;

	FragColor = vec4(result, 0.1);
}
