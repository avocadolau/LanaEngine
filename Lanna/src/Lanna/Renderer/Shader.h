#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


namespace Lanna {


    class Shader
    {
    public:
        // constructor generates the shader on the fly
        // ------------------------------------------------------------------------
        Shader(const char* fileName);

        // activate the shader
        // ------------------------------------------------------------------------
        void Init(const char* fileName);
        void Use();
        unsigned int GetID() { return ID; }
        void Delete();


        // utility uniform functions
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        
        void setVec2(const std::string& name, const glm::vec2& value) const;
        void setVec2(const std::string& name, float x, float y) const;
        void setVec3(const std::string& name, const glm::vec3& value) const;
        void setVec3(const std::string& name, float x, float y, float z) const;
        void setVec4(const std::string& name, const glm::vec4& value) const;
        void setVec4(const std::string& name, float x, float y, float z, float w) const;
        
        void setMat2(const std::string& name, const glm::mat2& mat) const;
        void setMat3(const std::string& name, const glm::mat3& mat) const;
        void setMat4(const std::string& name, const glm::mat4& mat) const;

    private:
        void checkCompileErrors(unsigned int shader, std::string type);
        std::string* Shader::getFileData(const char* file);

    private:
        unsigned int ID;
    };

}
#endif