#shader vertex

#version 430 core

layout(location = 0) in vec4 aPos;

void main()
{
	gl_Position = aPos;
};

#shader fragment

#version 430 core

out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
};