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
#include <map>
#include <utility>

#include "Helpers/FileHelpers.hpp"
#include "ShaderProgram.hpp"
#include "SceneObject.hpp"
#include "../Objects/Plane.hpp"
#include "Camera.hpp"
#include "Light.hpp"


using namespace std;



class Engine{
private:
    GLFWwindow *window;
    Camera *mainCamera;

    float delta;

    map<ShaderProgram*, vector<SceneObject *>> Objects;

    map<ShaderProgram *, map<char*, float> > SetUniformFloats;

    vector<Light *> Lights;




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

    void AddObjectToScene(ShaderProgram *program, SceneObject *object){
        Objects[program].push_back(object);
    }

    void setUniformFloat(ShaderProgram *p, char* name, float v){
        SetUniformFloats[p][name] = v;
    }

    void DrawScene(ShaderProgram* program){

        for(auto& program: Objects){
            ShaderProgram *p = program.first;

            p->Use();
            mainCamera->Use(p);

            for(auto& [name, f] : SetUniformFloats[p]){
                p->setUniformFloat(name, f);
            }

            for(int i = 0; i < program.second.size(); i++){
                program.second[i]->Draw(p);
            }

        }
    }



    void LightScene(Light* light){

    }






};


#endif //OPENGLPROJECT_MAINENGINE_HPP
