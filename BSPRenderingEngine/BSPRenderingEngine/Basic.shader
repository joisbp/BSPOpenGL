#shader vertex	//Type = 0 // Stream[0]

#version 430 core

layout (location = 0) in vec4 aPos;
layout(location = 1) in vec2 texC;

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

uniform sampler2D sampleTexture;
uniform sampler2D faceTexture;

void main()
{
	FragColor = mix(texture(sampleTexture, texCoord), texture(faceTexture, texCoord), 0.3f);
};


/*
	Basic.vs
	Basic.fs
*/