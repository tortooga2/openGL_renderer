//
// Created by Chase Nagle on 11/29/24.
//

#ifndef OPENGLPROJECT_MAINENGINE_HPP
#define OPENGLPROJECT_MAINENGINE_HPP

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

#include "./Helpers/FileHelpers.hpp"
#include "./ShaderObject.hpp"
#include "./SceneObject.hpp"
#include "../Objects/Plane.hpp"
#include "./Camera.hpp"


using namespace std;



class Engine{
private:
    GLFWwindow *window;
    Camera *mainCamera;

    float delta;




public:
    Engine(GLFWwindow *w) {
        window = w;
    };


    void Setup();
    void Update();
    void Draw();

    bool isKeyDown(int KeyCode){
        return glfwGetKey(window, KeyCode);
    }

    void KeyboardEvent();
    void GetTimeDelta(float dt){
        delta = dt;
    };

    void OnResize(float screenWidth, float screenHeight){

        mainCamera->UpdateAspectRatio(screenWidth, screenHeight);
    }






};


#endif //OPENGLPROJECT_MAINENGINE_HPP
