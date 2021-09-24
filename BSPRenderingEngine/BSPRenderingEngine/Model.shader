#shader vertex	//Type = 0 // Stream[0]

#version 430 core

layout(location = 0) in vec4 aPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 texC;

out vec2 texCoord;
out vec3 fNormal;
out vec3 wPos;

uniform mat4 world;
uniform mat4 proj;
uniform mat4 view;



void main()
{
	gl_Position = proj * view * world * aPos;
	texCoord = texC;
	fNormal = mat3(transpose(inverse(world))) * vNormal;
	wPos = mat3(world) * aPos.xyz;
};

#shader fragment	// type = 1 // stream[1]

#version 430 core

#define DIR_LIGHT
#define PNT_LIGHT
#define SPT_LIGHT

#if defined (DIR_LIGHT)
struct DLight
{
	vec3 Direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
#endif

#if defined (PNT_LIGHT)
struct PLight
{
	vec3 Position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};
#endif

#if defined (SPT_LIGHT)
struct SLight
{
	vec3 Position;
	vec3 Direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;
};
#endif

uniform vec4 color;

out vec4 FragColor;
in vec2 texCoord;
in vec3 fNormal;
in vec3 wPos;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform vec3 ambientColor;
uniform float ambientCoeff;
uniform vec3 viewPos;

#if defined(DIR_LIGHT)
uniform DLight dLight;
#endif

#if defined(PNT_LIGHT)
uniform PLight pLight[2];
#endif

#if defined(SPT_LIGHT)
uniform SLight sLight;
#endif

vec3 CalculateDirectionLight()
{
	vec3 color = vec3(0.0f);
#if defined(DIR_LIGHT)
	vec3 ambient = (ambientCoeff * dLight.ambient) * texture(diffuse0, texCoord).xyz;

	vec3 norm = normalize(fNormal);
	float diff = max(dot(norm, -dLight.Direction), 0.0);
	vec3 diffuse = diff * dLight.diffuse * texture(diffuse0, texCoord).xyz;

	vec3 viewDir = normalize(viewPos - wPos);
	vec3 reflectDir = reflect(-dLight.Direction, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = texture(specular0, texCoord).xyz * spec * dLight.specular;

	color = ambient + diffuse + specular;
#endif

	return color;
}

vec3 CalculatePointLight()
{
	vec3 color = vec3(0.0f);
#if defined (PNT_LIGHT)

	for (int i = 0; i < 2; ++i)
	{
		vec3 lightDir = normalize(pLight[i].Position - wPos);
		vec3 normal = normalize(fNormal);
		vec3 viewDir = normalize(viewPos - wPos);

		// diffuse shading
		float diff = max(dot(normal, lightDir), 0.0);
		// specular shading
		vec3 reflectDir = reflect(-lightDir, normal);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		// attenuation
		float distance = length(pLight[i].Position - wPos);
		float attenuation = 1.0 / (pLight[i].constant + pLight[i].linear * distance + pLight[i].quadratic * (distance * distance));
		// combine results
		vec3 ambient = pLight[i].ambient * texture(diffuse0, texCoord).xyz;
		vec3 diffuse = pLight[i].diffuse * diff * texture(diffuse0, texCoord).xyz;
		vec3 specular = pLight[i].specular * spec * texture(specular0, texCoord).xyz;

		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;

		color += ambient + diffuse + specular;
	}

#endif

	return color;
}

vec3 CalculateSpotLight()
{
	vec3 color = vec3(0.0f);

#if defined (SPT_LIGHT)
	vec3 lightDir = normalize(sLight.Position - wPos);
	vec3 normal = normalize(fNormal);
	vec3 viewDir = normalize(viewPos - wPos);

	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	// attenuation
	float distance = length(sLight.Position - wPos);
	float attenuation = 1.0 / (sLight.constant + sLight.linear * distance + sLight.quadratic * (distance * distance));
	// spotlight intensity

	float theta = dot(lightDir, normalize(-sLight.Direction));
	float epsilon = sLight.cutOff - sLight.outerCutOff;
	float intensity = clamp((theta - sLight.outerCutOff) / epsilon, 0.0, 1.0);

	// combine results
	vec3 ambient = sLight.ambient * vec3(texture(diffuse0, texCoord));
	vec3 diffuse = sLight.diffuse * diff * vec3(texture(diffuse0, texCoord));
	vec3 specular = sLight.specular * spec * vec3(texture(specular0, texCoord));
	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;
	color = (ambient + diffuse + specular);

#endif 

	return color;
}

void main()
{
	vec3 color = vec3(0.0f);

	color += CalculateDirectionLight();
	color += CalculatePointLight();
	color += CalculateSpotLight();

	FragColor = vec4(color, 1.0f);
};


// Phong
// Gaurrad 

/*
	// Global Ambient Colorw
	// Ambient Coeff

*/

/*
	// Diffuse Coefficient

	// Dot Product( Normal and LightDir)

*/

/*
	// Specular Coefficient
	// View direction and Light Direction and your Normal

	//
	dot of Normal and HalfVector
*/

/*
	Directional ( Direction)
	PointLights ( Position )
	SpotLights (D + P)

*/

/*
	Basic.vs
	Basic.fs
*/