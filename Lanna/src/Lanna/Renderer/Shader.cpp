#include "lnpch.h"
#include "Shader.h"

#include <glew.h>
#include <glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Lanna/Log.h"


namespace Lanna {

    Shader::Shader(const char* fileName)
    {
        Init(fileName);
    }

    void Shader::Init(const char* fileName)
    {

        std::string vertexFile = fileName;
        vertexFile += ".vs";

        std::string fragmentFile = fileName;
        fragmentFile += ".fs";

        std::string geometryFile = fileName;
        geometryFile += ".gs";

        std::string* vertexShaderSourceStr = getFileData(vertexFile.c_str());

        if (!vertexShaderSourceStr) {
            std::string msg = "Couldn't open file: ";
            msg += vertexFile;

                return;
        }

        const char* vertexShaderSource = vertexShaderSourceStr->c_str();

        std::string* fragmentShaderSourceStr = getFileData(fragmentFile.c_str());

        if (!fragmentShaderSourceStr) {
            std::string msg = "Couldn't open file: ";
            msg += fragmentFile;

         
                return;
        }

        const char* fragmentShaderSource = fragmentShaderSourceStr->c_str();

        std::string* geometryShaderSourceStr = getFileData(geometryFile.c_str());
        bool hasGS = geometryShaderSourceStr;




        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        int success;
        char infoLog[512];

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);

            std::string msg = "Vertex shader compile error: ";
            msg += infoLog;

           

                return;
        }

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::string msg = "Fragment shader compile error: ";
            msg += infoLog;

           

                return;
        }

        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);


        unsigned int geometryShader;
        if (hasGS)
        {
            const char* geometryShaderSource = geometryShaderSourceStr->c_str();
            geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometryShader, 1, &geometryShaderSource, NULL);
            glCompileShader(geometryShader);

            glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);

            if (!success) {
                glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
                std::string msg = "Geometry shader compile error: ";
                msg += infoLog;

              

                    return;
            }
            glAttachShader(ID, geometryShader);
        }

        glLinkProgram(ID);

        glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(ID, 512, NULL, infoLog);
            std::string msg = "Shader program compile error: ";
            msg += infoLog;

  

           return;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        if (hasGS)
            glDeleteShader(geometryShader);

        if(success)
            LN_CORE_INFO("The shader with filname {0} has been loaded succesfully!", fileName);

        delete vertexShaderSourceStr;
        delete fragmentShaderSourceStr;
        delete geometryShaderSourceStr;
    }

    void Shader::Use()
    {
        glUseProgram(ID);
    }

    void Shader::Delete()
    {
        glDeleteProgram(ID);
    }

    void Shader::setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void Shader::setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void Shader::setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::setVec2(const std::string& name, const glm::vec2& value) const
    {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void Shader::setVec2(const std::string& name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }

    void Shader::setVec3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void Shader::setVec3(const std::string& name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }

    void Shader::setVec4(const std::string& name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }

    void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    unsigned int Shader::getUniformLocation(const char* uniform_name)
    {
        return glGetUniformLocation(ID, uniform_name);
    }


    void Shader::checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }


    std::string* Shader::getFileData(const char* file)
    {
        std::fstream shaderFile;

        shaderFile.open(file, std::ios::in);

        if (!shaderFile.is_open()) return NULL;

        std::stringstream buffer;

        buffer << shaderFile.rdbuf();

        shaderFile.close();

        return new std::string(buffer.str());
    }
}