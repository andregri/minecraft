#include "include/shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string & vertexShaderPath, const std::string & fragmentShaderPath) {
    mShader = glCreateProgram();
    unsigned int vertexShader = Compile(vertexShaderPath, GL_VERTEX_SHADER);
    unsigned int fragmentShader = Compile(fragmentShaderPath, GL_FRAGMENT_SHADER);
    glAttachShader(mShader, vertexShader);
    glAttachShader(mShader, fragmentShader);
    glLinkProgram(mShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

//Shader::~Shader() {
//    glUseProgram(0);
//    glDeleteProgram(mShader);
//}

void Shader::Use() const {
    glUseProgram(mShader);
}

void Shader::SetUniform1i(const std::string & name, int value) const {
    Use();
    int location = glGetUniformLocation(mShader, name.c_str());
    if (location < 0) {
        std::cout << "Uniform " << name << " not found!\n";
        return;
    }
    glUniform1i(location, value);
    glUseProgram(0);
}

void Shader::SetUniformVec4f(const std::string & name, const glm::vec4& value) const {
    Use();
    int location = glGetUniformLocation(mShader, name.c_str());
    if (location < 0) {
        std::cout << "Uniform " << name << " not found!\n";
        return;
    }
    glUniform4fv(location, 1, &value[0]);
    glUseProgram(0);
}

void Shader::SetUniformMatrix4f(const std::string & name, const glm::mat4 & value) const {
    Use();
    int location = glGetUniformLocation(mShader, name.c_str());
    if (location < 0) {
        std::cout << "Uniform " << name << " not found!\n";
        return;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
    glUseProgram(0);
}

unsigned int Shader::Compile(const std::string & sourcePath, unsigned int vertexType) {
    std::string sourceCode;

    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(sourcePath);
        std::stringstream stream;
        stream << file.rdbuf();
        sourceCode = stream.str();
        file.close();        
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::VERTEX_SHADER::FILE_NOT_SUCCESSFULLY_READ\n";
    }
    const char * sourceCodeCstr = sourceCode.c_str();
    unsigned int shader = glCreateShader(vertexType);
    glShaderSource(shader, 1, &sourceCodeCstr, NULL);
    glCompileShader(shader);

    GLint vertex_compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &vertex_compiled);
    if (vertex_compiled != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(shader, 1024, &log_length, message);
        // Write the error to a log
        std::cout << "Compile Error: " << message << std::endl;
    }

    return shader;
}