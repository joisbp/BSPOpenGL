#shader vertex

#version 430 core

layout(location = 0) in vec4 aPos;
layout(location = 1) in vec3 color;

out vec3 fcolor;

void main()
{
	gl_Position = aPos;
	fcolor = color;
};

#shader fragment

#version 430 core

out vec4 FragColor;
in vec3 fcolor;

void main()
{
	FragColor = vec4(fcolor, 1.0f);
};