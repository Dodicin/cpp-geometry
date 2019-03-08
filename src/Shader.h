#pragma once

#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader
{
private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;

public:
    Shader(const std::string& filepath);
    ~Shader();

    void bind() const;
    void unbind() const;
    
    // Set uniforms
    void setUniform4f(const std::string& name, float v0, float v1, float f2, float f3);

private:
    unsigned int getUniformLocation(const std::string& name);
    unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int compileShader(unsigned int type, const std::string& source);
    ShaderProgramSource parseShader(const std::string& filepath);
};