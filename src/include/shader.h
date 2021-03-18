#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class Shader {
    public:
        Shader(const std::string & vertexShaderPath, const std::string & fragmentShaderPath);
        //~Shader();
        void Use() const;

        void SetUniform1i(const std::string & name, int value) const;
        void SetUniformVec4f(const std::string & name, const glm::vec4&) const;
        void SetUniformMatrix4f(const std::string & name, const glm::mat4 & value) const;

    private:
        unsigned int mShader;

        unsigned int Compile(const std::string & sourcePath, unsigned int vertexType);
};

#endif