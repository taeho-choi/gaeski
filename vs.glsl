// This is Vertex Shader

#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vTexCoord;
layout (location = 2) in vec3 vNormal;

uniform mat4 transform; 
uniform mat4 projectionTransform;

out vec2 TexCoord;
out vec3 passColor;
out vec3 Normal;
out vec3 FragPos;

void main()
{
	gl_Position =   projectionTransform * transform * vec4(vPos, 1.0);

	TexCoord = vec2(vTexCoord.x, vTexCoord.y);
	FragPos = vec3(transform * vec4(vPos, 1.0));

	Normal = normalize(mat3(transpose(inverse(transform))) * vNormal);
}
