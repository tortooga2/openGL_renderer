//
// Created by Chase Nagle on 11/29/24.
//

#ifndef OPENGLPROJECT_GROUND_HPP
#define OPENGLPROJECT_GROUND_HPP

#include <vector>

#include "../Components/SceneObject.hpp"
#include "../Components/ShaderProgram.hpp"
#include "Globals.hpp"





class Plane : public SceneObject{
private:




public:

    Plane(int rows, int columns) : SceneObject(GeneratePlane( (2.0/rows), rows, columns)){

    }

    vector<Vertex> GeneratePlane(float size, float rows, float columns){
        vector<Vertex> outMesh;
        vector<Vertex> tempMesh;
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


                tempMesh.push_back(v);
            }
        }
        for (int x = 0; x < columns - 1; x++) {
            for (int z = 0; z < rows - 1; z++) {
                unsigned int topLeft = x * rows + z;
                unsigned int topRight = topLeft + 1;
                unsigned int bottomLeft = (x + 1) * (rows) + z;
                unsigned int bottomRight = bottomLeft + 1;

                // First triangle (top-left, bottom-left, top-right)
                outMesh.push_back(tempMesh[topLeft]);
                outMesh.push_back(tempMesh[bottomLeft]);
                outMesh.push_back(tempMesh[topRight]);

                // Second triangle (top-right, bottom-left, bottom-right)
                outMesh.push_back(tempMesh[topRight]);
                outMesh.push_back(tempMesh[bottomLeft]);
                outMesh.push_back(tempMesh[bottomRight]);
            }
        }

        return outMesh;

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

};

#endif //OPENGLPROJECT_GROUND_HPP
