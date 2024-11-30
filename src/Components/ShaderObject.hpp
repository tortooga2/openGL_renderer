//
// Created by Chase Nagle on 11/16/24.
//

#ifndef OPENGLPROJECT_SHADEROBJECT_HPP
#define OPENGLPROJECT_SHADEROBJECT_HPP

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>



class ShaderObject {
private:
    unsigned int shaderProgram;



public:
    ShaderObject(std::string fragment, std::string vertex){
        unsigned int fragmentShader;
        unsigned int vertexShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        vertexShader = glCreateShader(GL_VERTEX_SHADER);

        GLint success;
        const char* vertShader = vertex.c_str();

        glShaderSource(vertexShader, 1, &vertShader, NULL);
        glCompileShader(vertexShader);

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cerr << "Shader Compilation Error:\n" << infoLog << std::endl;
        }

        const char* fragShader = fragment.c_str();
        glShaderSource(fragmentShader, 1, &fragShader, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cerr << "Shader Compilation Error:\n" << infoLog << std::endl;
        }

        this->shaderProgram = glCreateProgram();
        glAttachShader(this->shaderProgram, vertexShader);
        glAttachShader(this->shaderProgram, fragmentShader);
        glLinkProgram(this->shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }


    ShaderObject(){
        const char* fragShader = "#version 330 core\n"
                                 "out vec4 FragColor;\n"
                                 "\n"
                                 "void main()\n"
                                 "{\n"
                                 "    FragColor = vec4(1.0f, 1.0f, 0.5f, 1.0f);\n"
                                 "} ";

        const char* vertShader = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";



        unsigned int fragmentShader;
        unsigned int vertexShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        vertexShader = glCreateShader(GL_VERTEX_SHADER);

        GLint success;

        glShaderSource(vertexShader, 1, &vertShader, NULL);
        glCompileShader(vertexShader);

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cerr << "Shader Compilation Error:\n" << infoLog << std::endl;
        }

        glShaderSource(fragmentShader, 1, &fragShader, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cerr << "Shader Compilation Error:\n" << infoLog << std::endl;
        }

        this->shaderProgram = glCreateProgram();
        glAttachShader(this->shaderProgram, vertexShader);
        glAttachShader(this->shaderProgram, fragmentShader);
        glLinkProgram(this->shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void setUniformMat4x4(const char* matrixName, glm::mat4x4 &modelMatrix) const{
        GLint matLocation = glGetUniformLocation(shaderProgram, matrixName);
        glUniformMatrix4fv(matLocation, 1, GL_FALSE, &modelMatrix[0][0]);
    }

    void setUniformFloat(const char* floatName, float &f){
        GLint loc = glGetUniformLocation(shaderProgram, floatName);
        glUniform1f(loc, f);
    }

    void setUniformVec4(char* vecName, glm::vec4 &Vector4) const{
        GLint vecLocation = glGetUniformLocation(shaderProgram, vecName);
        glUniform4f(vecLocation, Vector4.r, Vector4.g, Vector4.b, Vector4.a);
    }

    void Use() const{
        glUseProgram(this->shaderProgram);
    }

    ~ShaderObject(){
        glDeleteProgram(this->shaderProgram);
    }




};


#endif //OPENGLPROJECT_SHADEROBJECT_HPP
