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

using namespace std;

class ShaderObject {
private:
    unsigned int shaderProgram;



public:
    ShaderObject(std::string fragmentPath, std::string vertexPath){

        string fragSource = loadShaderSource(fragmentPath);
        string vertSource = loadShaderSource(vertexPath);


        const char* fragShader = fragSource.c_str();
        const char* vertShader = vertSource.c_str();

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
            std::cerr << "Vertex Compilation Error:\n" << infoLog << std::endl;
        }


        glShaderSource(fragmentShader, 1, &fragShader, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cerr << "Fragment Compilation Error:\n" << infoLog << std::endl;
        }

        this->shaderProgram = glCreateProgram();
        glAttachShader(this->shaderProgram, vertexShader);
        glAttachShader(this->shaderProgram, fragmentShader);
        glLinkProgram(this->shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    ShaderObject(string fragmentPath, string vertexPath, string geoPath){
        string fragSource = loadShaderSource(fragmentPath);
        string vertSource = loadShaderSource(vertexPath);
        string geoSource = loadShaderSource(geoPath);


        const char* fragShader = fragSource.c_str();
        const char* vertShader = vertSource.c_str();
        const char* geoShader = geoSource.c_str();



        unsigned int fragmentShader;
        unsigned int vertexShader;
        unsigned int geomatryShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        geomatryShader = glCreateShader(GL_GEOMETRY_SHADER);

        GLint success;


        glShaderSource(vertexShader, 1, &vertShader, NULL);
        glCompileShader(vertexShader);


        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cerr << "Vertex Compilation Error:\n" << infoLog << std::endl;
        }

        glShaderSource(fragmentShader, 1, &fragShader, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cerr << "Fragment Compilation Error:\n" << infoLog << std::endl;
        }


        glShaderSource(geomatryShader, 1, &geoShader, NULL);
        glCompileShader(geomatryShader);
        glGetShaderiv(geomatryShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cerr << "Geomatry Compilation Error:\n" << infoLog << std::endl;
        }


        this->shaderProgram = glCreateProgram();
        glAttachShader(this->shaderProgram, vertexShader);
        glAttachShader(this->shaderProgram, fragmentShader);
        glAttachShader(this->shaderProgram, geomatryShader);
        glLinkProgram(this->shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteShader(geomatryShader);
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

    void setUniformSampler2D(char* name, unsigned int Texture) const{
        // Activate texture unit 0
        glActiveTexture(GL_TEXTURE0);
        // Bind your texture
        glBindTexture(GL_TEXTURE_2D, Texture);
        // Set the sampler uniform in your shader to use texture unit 0
        int samplerLocation = glGetUniformLocation(shaderProgram, name);
        glUniform1i(samplerLocation, 0);

    }

    void Use() const{
        glUseProgram(this->shaderProgram);
    }

    void StopUsing() const{
        glUseProgram(0);
    }

    ~ShaderObject(){
        glDeleteProgram(this->shaderProgram);
    }




};


#endif //OPENGLPROJECT_SHADEROBJECT_HPP
