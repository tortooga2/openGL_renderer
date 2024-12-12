//
// Created by Chase Nagle on 12/9/24.
//

#ifndef OPENGLPROJECT_FULLSCREENQUAD_HPP
#define OPENGLPROJECT_FULLSCREENQUAD_HPP

#include "../Components/SceneObject.hpp"

using namespace std;

class FullScreenQuad : public SceneObject {

public:
    FullScreenQuad() : SceneObject(GenerateQuad()){

    }

    vector<Vertex> GenerateQuad() {
        vector<Vertex> mesh;

        // Define two triangles to form a quad
        // First Triangle (Bottom-left, Bottom-right, Top-right)
        mesh.push_back({{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}}); // Bottom-left (Red)
        mesh.push_back({{ 1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}); // Bottom-right (Green)
        mesh.push_back({{ 1.0f,  1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}); // Top-right (Blue)

        // Second Triangle (Top-right, Top-left, Bottom-left)
        mesh.push_back({{ 1.0f,  1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}); // Top-right (Blue)
        mesh.push_back({{-1.0f,  1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f}}); // Top-left (Yellow)
        mesh.push_back({{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}}); // Bottom-left (Red)

        return mesh;
    }

};


#endif //OPENGLPROJECT_FULLSCREENQUAD_HPP
