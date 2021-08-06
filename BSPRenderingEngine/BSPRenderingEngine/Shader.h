#pragma once
#include <string>
#include <unordered_map>

struct ShaderSources
{
	std::string vertexShader;
	std::string fragmentShader;
};

class Shader
{
private:
	unsigned int m_ShaderID;

	std::unordered_map<std::string, int> m_UniformMap;
public:
	Shader(const std::string& filePath);
	~Shader();


	ShaderSources ParseShader(const std::string& filePath);
	//std::pair<std::string, std::string> ParseShader(const std::string& filePath);

	unsigned int CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

	unsigned int CompileShader(int shaderType, const std::string& shaderSource);

	void Bind() const;

	void UnBind() const;
	
	void SetUniform4(const std::string& name, float r, float g, float b, float a);

	void SetUniform1(const std::string& name, int value);

	//void SetMatrix4(const std::string& name, glm::mat4& matrix);

	unsigned int GetLocation(const std::string& name);
};