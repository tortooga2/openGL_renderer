//
// Created by Chase Nagle on 11/29/24.
//

#ifndef OPENGLPROJECT_SCENEOBJECT_HPP
#define OPENGLPROJECT_SCENEOBJECT_HPP


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

#include "./Globals.hpp"



using namespace std;









class SceneObject{
public:
    vector<Vertex> Mesh;
    unsigned int VAO, VBO;
    unsigned int NBO;

    Vector3 position = {0.0f, 0.0f, 0.0f};
    Vector3 scale = {1.0f, 1.0f, 1.0f};
    Vector3 rotation = {0.0f, 0.0f, 0.0f};




public:
    SceneObject(vector<Vertex> mesh){
        Mesh = mesh;

        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &NBO);

        glBindVertexArray(VAO);
        //Bind Mesh Data
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, this->Mesh.size() * sizeof(Vertex), Mesh.data(), GL_STATIC_DRAW);
        //Structure Vertex Attributes

        //Positions (location = 0)

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);
        //Normals (location = 1)
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(1);
        //Color (location = 2
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);


    };


    void Draw(ShaderObject *shaderObject){
        //Bind Transformations
        glm::mat4x4 translateMatrix = glm::mat4x4(1.0f, 0.0f, 0.0f, 0.0f,
                                                  0.0f, 1.0f, 0.0f, 0.0f,
                                                  0.0f, 0.0f, 1.0f, 0.0f,
                                                  position.x, position.y, position.z, 1.0f);

        glm::mat4x4 scalingMatrix = glm::mat4x4(scale.x, 0.0f, 0.0f, 0.0f,
                                                0.0f, scale.y, 0.0f, 0.0f,
                                                0.0f, 0.0f, scale.z, 0.0f,
                                                0.0f, 0.0f, 0.0f, 1.0f);



        glm::mat4x4 rotateX = glm::mat4x4(1.0f, 0.0f, 0.0, 0.0f,
                                          0.0f, cos(rotation.x), sin(rotation.x), 0.0f,
                                          0.0f, -sin(rotation.x), cos(rotation.x), 0.0f,
                                          0.0f, 0.0f, 0.0f, 1.0f);


        glm::mat4x4 rotateY = glm::mat4x4(cos(rotation.y), 0.0f, -sin(rotation.y), 0.0f,
                                          0.0f, 1.0f, 0.0f, 0.0f,
                                          sin(rotation.y), 0.0f, cos(rotation.y), 0.0f,
                                          0.0f, 0.0f, 0.0f, 1.0f);

        glm::mat4x4 rotateZ = glm::mat4x4(cos(rotation.z), sin(rotation.z), 0.0f, 0.0f,
                                          -sin(rotation.z), cos(rotation.z), 0.0f, 0.0f,
                                          0.0f, 0.0f, 1.0f, 0.0f,
                                          0.0f, 0.0f, 0.0f, 1.0f);

        glm::mat4x4 modelMatrix = translateMatrix * (rotateZ * rotateY * rotateX) * scalingMatrix;

        shaderObject->setUniformMat4x4("ModelMatrix", modelMatrix);

        glBindVertexArray(VAO);
        int vertexCount = static_cast<int>(Mesh.size());
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        glBindVertexArray(0);
    }



    SceneObject(){
        Mesh = {
                // Front face (RED)
                {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},  // Bottom-left
                {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},  // Bottom-right
                {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},  // Top-right
                {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},  // Bottom-left
                {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},  // Top-right
                {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},  // Top-left

                // Back face (ORANGE)
                {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.5f, 0.0f}},
                {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.5f, 0.0f}},
                {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.5f, 0.0f}},
                {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.5f, 0.0f}},
                {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.5f, 0.0f}},
                {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.5f, 0.0f}},

                // Top face (YELLOW)
                {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}},
                {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}},
                {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}},
                {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}},
                {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}},
                {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}},

                // Bottom face (GREEN)
                {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
                {{ 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
                {{ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
                {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
                {{ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
                {{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},

                // Right face (BLUE)
                {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
                {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
                {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
                {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
                {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
                {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},

                // Left face (PURPLE)
                {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.5f, 0.0f, 0.5f}},
                {{-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.5f, 0.0f, 0.5f}},
                {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.5f, 0.0f, 0.5f}},
                {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.5f, 0.0f, 0.5f}},
                {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.5f, 0.0f, 0.5f}},
                {{-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.5f, 0.0f, 0.5f}}
        };;

        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &NBO);

        glBindVertexArray(VAO);
        //Bind Mesh Data
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, this->Mesh.size() * sizeof(Vertex), Mesh.data(), GL_STATIC_DRAW);
        //Structure Vertex Attributes

        //Positions (location = 0)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);
        //Normals (location = 1)
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(1);
        //Color (location = 2
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);

    }
};

#endif //OPENGLPROJECT_SCENEOBJECT_HPP
