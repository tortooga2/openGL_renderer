//
// Created by Chase Nagle on 11/29/24.
//

#include "mainEngine.hpp"


ShaderObject* program;
SceneObject* object;
SceneObject* object2;
Camera* camera;

float rotation = 0.0f;

Vector3 CameraPos = {0.0f, 0.0f, -0.01f};



void Engine::Setup(){

    string fragmentShader = loadShaderSource("Content/Shaders/Tests/light.frag");
    string vertexShader = loadShaderSource("Content/Shaders/Tests/light.vert");

    program = new ShaderObject(fragmentShader, vertexShader);
    object = new SceneObject();
    object2 = new SceneObject();
    object2->position = Vector3{-0.5f, 0.0f, 0.0f};
    object->position = Vector3{0.5f, 0.0f, 0.0f};
    camera = new Camera();

}


void Engine::Update() {

    object->rotation = {rotation, 0.0f, rotation};
    object2->rotation = {-rotation, 0.0f, -rotation};
    if(isKeyDown(GLFW_KEY_E)) {
        rotation += 0.006;
    }
    if(isKeyDown(GLFW_KEY_Q)) {
        rotation -= 0.006;
    }

}
//-----How to Use Draw Loop------
//1) Use a shader program (ShaderObject.Use()). This should be created in setup
//2) Use a camera if you want (Camera.Use()). This should be created in setup
//3) Draw SceneObject (SceneObject.Draw()).

void Engine::Draw() {
    program->Use();
    camera->Use(program);
    object->Draw(program);
    object2->Draw(program);


}