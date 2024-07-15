#pragma once

#include<string>
#include<Unordered_map>

struct ShaderSources {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUnifrom1i(const std::string& name, int value);
	void SetUnifrom1f(const std::string& name, float value);
	void SetUnifrom4f(const std::string& name, float v0, float v1 , float v2, float v3);
private:
	ShaderSources ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUnifromLocation(const std::string& name);
};