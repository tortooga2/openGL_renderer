//
// Created by Chase Nagle on 11/29/24.
//

#ifndef OPENGLPROJECT_GROUND_HPP
#define OPENGLPROJECT_GROUND_HPP

#include <vector>

#include "../Components/SceneObject.hpp"
#include "../Components/ShaderObject.hpp"
#include "Globals.hpp"





class Plane{
private:
    //Choosing indexed rendering to allow more straight forward editing on CPU.
    vector<Vertex> Mesh;
    vector<int> Indices;

    unsigned int VAO, VBO;
    unsigned int IBO;
    unsigned int NBO;


    Vector3 position = {0.0f, 0.0f, 0.0f};
    Vector3 scale = {1.0f, 1.0f, 1.0f};
    Vector3 rotation = {0.0f, 0.0f, 0.0f};


public:

    Plane(int rows, int columns){
        float size = 2.0 / rows;
        GeneratePlane(size, rows, columns, Mesh, Indices);

        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &NBO);
        glGenBuffers(1, &IBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, this->Mesh.size() * sizeof(Vertex), Mesh.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);
        //Normals (location = 1)
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(1);
        //Color (location = 2
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(int), Indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);

    }

    void GeneratePlane(float size, float rows, float columns, vector<Vertex> &outMesh, vector<int> &outIndices){
        for(int x = 0; x < columns; x++){
            for(int z = 0; z < rows; z++){
                Vertex v;
                v.position[0] = x * size;
                v.position[1] = 0;
                v.position[2] = z * size;

                v.normal[0] = 0.0;
                v.normal[1] = 1.0;
                v.normal[2] = 0.0;

                v.color[0] = 0.8f;
                v.color[1] = 0.5f;
                v.color[2] = 1.0f;


                outMesh.push_back(v);
            }
        }
        for (int x = 0; x < columns - 1; x++) {
            for (int z = 0; z < rows - 1; z++) {
                unsigned int topLeft = x * rows + z;
                unsigned int topRight = topLeft + 1;
                unsigned int bottomLeft = (x + 1) * (rows) + z;
                unsigned int bottomRight = bottomLeft + 1;

                // First triangle (top-left, bottom-left, top-right)
                outIndices.push_back(topLeft);
                outIndices.push_back(bottomLeft);
                outIndices.push_back(topRight);

                // Second triangle (top-right, bottom-left, bottom-right)
                outIndices.push_back(topRight);
                outIndices.push_back(bottomLeft);
                outIndices.push_back(bottomRight);
            }
        }

    }

    void SetRotation(Vector3 newRotation){
        rotation = newRotation;
    };

    void UpdateRotationX(float x){
        rotation.x = x;
    }
    void UpdateRotationY(float y){
        rotation.y = y;
    }
    void UpdateRotationZ(float z){
        rotation.z = z;
    }

    void SetScale(Vector3 newRotation){
        scale = newRotation;
    };

    void UpdateScaleX(float x){
        scale.x = x;
    }
    void UpdateScaleY(float y){
        scale.y = y;
    }
    void UpdateScaleZ(float z){
        scale.z = z;
    }

    void Use(ShaderObject *shaderObject){
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
        int vertexCount = static_cast<int>(Indices.size());
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //glLineWidth(5.0f);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);


        glBindVertexArray(0);


//        glPointSize(10.0f);
//        glBindVertexArray(VAO);
//        glDrawArrays(GL_POINTS, 0, Mesh.size());



    }

};

#endif //OPENGLPROJECT_GROUND_HPP
