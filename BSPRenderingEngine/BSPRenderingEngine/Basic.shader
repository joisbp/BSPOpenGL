#shader vertex	//Type = 0 // Stream[0]

#version 430 core

layout (location = 0) in vec4 aPos;

void main()
{
	gl_Position = aPos;
};

#shader fragment	// type = 1 // stream[1]

#version 430 core

uniform vec4 color;

out vec4 FragColor;

void main()
{
	FragColor = color;
};


/*
	Basic.vs
	Basic.fs
*/