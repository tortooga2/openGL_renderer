//
// Created by Chase Nagle on 11/29/24.
//

#include "mainEngine.hpp"


ShaderProgram* basicProgram;
ShaderProgram* waveProgram;
Plane* wave;
Plane* g2;
SceneObject* object;





float t = 0.0f;
float speed = 4.0f;

void Engine::Setup(){
    mainCamera = new Camera();

    basicProgram = new ShaderProgram("Content/Shaders/Tests/basic.frag", "Content/Shaders/Tests/basic.vert");
    waveProgram = new ShaderProgram("Content/Shaders/Tests/wave.frag", "Content/Shaders/Tests/wave.vert", "Content/Shaders/Tests/wave.geom");

    g2 = new Plane(300, 300);
    g2->SetRotation(Vector3{0.0f, 0.0f, 0.0f});
    g2->SetScale(Vector3{10.0f, 10.0, 10.0f});

    object = new SceneObject();
    object->position = Vector3{10, 1, 10};

    wave = new Plane(300, 300);


    AddObjectToScene(basicProgram, g2);
    AddObjectToScene(basicProgram, object);

    AddObjectToScene(waveProgram, wave);

}


void Engine::Update() {
    setUniformFloat(waveProgram, "time", t+=0.01);
    object->rotation += Vector3{1.0f * delta, 0.0, 1.0f * delta};


}



void Engine::Draw() {
    DrawScene(basicProgram);
}




void Engine::KeyboardEvent(){
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