//
// Created by Chase Nagle on 11/29/24.
//

#include "mainEngine.hpp"


//ShaderObject* waveProgram;
ShaderObject* basicProgram;

//Plane* g;
Plane* g2;


SceneObject* object;






float rotation = 0.0f;

Vector3 CameraPos = {0.0f, 0.0f, -0.01f};

float t = 0.0f;

float speed = 4.0f;

void Engine::Setup(){
    mainCamera = new Camera();

//    waveProgram = new ShaderObject("Content/Shaders/Tests/light.frag", "Content/Shaders/Tests/light.vert", "Content/Shaders/Tests/light.geom");
    basicProgram = new ShaderObject("Content/Shaders/Tests/frag.glsl", "Content/Shaders/Tests/vert.glsl");

//    g = new Plane(300, 300);
    g2 = new Plane(300, 300);
//    g->SetRotation(Vector3{0.0f, 0.0f, 0.0f});
//    g->SetScale(Vector3{10.0f, 10.0, 10.0f});
    g2->SetRotation(Vector3{0.0f, 0.0f, 0.0f});
    g2->SetScale(Vector3{10.0f, 10.0, 10.0f});

    object = new SceneObject();

    object->position = Vector3{10, 1, 10};






}


void Engine::Update() {

    t+=0.01;
    object->rotation += Vector3{1.0f * delta, 0.0, 0.0};


}

//-----How to Use Draw Loop------
//1) Use a shader program (ShaderObject.Use()). This should be created in setup
//2) Use a mainCamera if you want (mainCamera.Use()). This should be created in setup
//3) Draw SceneObject (SceneObject.Draw()).

void Engine::Draw() {
//    waveProgram->Use();
//    waveProgram->setUniformFloat("time", t);
//    mainCamera->Use(waveProgram);
//    g->Use(waveProgram);



    basicProgram->Use();

    mainCamera->Use(basicProgram);
    object->Draw(basicProgram);
    g2->Use(basicProgram);

}




void Engine::KeyboardEvent(){
    if(isKeyDown(GLFW_KEY_E)) {
        rotation += 0.006;
    }
    if(isKeyDown(GLFW_KEY_Q)) {
        rotation -= 0.006;
    }
    if(isKeyDown(GLFW_KEY_W)){
        mainCamera->Position += mainCamera->Front * speed * delta;
    }
    if(isKeyDown(GLFW_KEY_S)){
        mainCamera->Position -= mainCamera->Front * speed * delta;
    }
    if(isKeyDown(GLFW_KEY_A)){
        mainCamera->Position -= glm::normalize(glm::cross(mainCamera->Front, mainCamera->Up)) * speed * delta;
    }
    if(isKeyDown(GLFW_KEY_D)){
        mainCamera->Position += glm::normalize(glm::cross(mainCamera->Front, mainCamera->Up)) * speed * delta;
    }
    if(isKeyDown(GLFW_KEY_SPACE)){
        mainCamera->Position.y += speed * delta;
    }
    if(isKeyDown(GLFW_KEY_LEFT_SHIFT)){
        mainCamera->Position.y -= speed * delta;
    }

    if(isKeyDown(GLFW_KEY_UP)){
        mainCamera->Pitch += 0.6;
    }
    if(isKeyDown(GLFW_KEY_DOWN)){
        mainCamera->Pitch -= 0.6;
    }
    if(isKeyDown(GLFW_KEY_RIGHT)){
        mainCamera->Yaw += 0.6;
    }
    if(isKeyDown(GLFW_KEY_LEFT)){
        mainCamera->Yaw -= 0.6;
    }
    mainCamera->updateCameraVectors();
}