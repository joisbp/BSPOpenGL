#shader vertex	//Type = 0 // Stream[0]

#version 430 core

layout(location = 0) in vec4 aPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 texC;

out vec2 texCoord;

uniform mat4 world;
uniform mat4 proj;
uniform mat4 view;

void main()
{
	gl_Position = proj * view * world * aPos;
	texCoord = texC;
};

#shader fragment	// type = 1 // stream[1]

#version 430 core

uniform vec4 color;

out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

void main()
{
	FragColor = mix(texture(diffuse0, texCoord), texture(specular0, texCoord), 1.0f);
};


/*
	Basic.vs
	Basic.fs
*/