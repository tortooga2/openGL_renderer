//
// Created by Chase Nagle on 11/29/24.
//

#include "mainEngine.hpp"


ShaderProgram* basicProgram;
ShaderProgram* matProgram;

Plane* g2;
SceneObject* object;
SceneObject* object2;

SceneObject* l;


/*light is a Class variable for easier usage. Look in DrawScene to see how we set the depthMap texture (GL_TEXTURE1)
 * ... And any other uniform info.
 *
 * To expand further on the general structure of the lighting shaders. All found in Content/Shaders/Lighting.
 * Shaded.frag/vert is simple taking in the preset info and as well as the depthMap and lightViewMatrix in order to get fragments in shadow.
 * light.frag/vert is simple meant to create the depth map texture.
 * the stuff in the Debug folder is meant to display the depthMap on a static Quad.
 *
 */

//FullScreenQuad* DebugSurface; Full screen Quad to view depth texture.



//Comments:
// Shaded.frag is meant to be a simple shader that does take into account



float t = 0.0f;
float speed = 4.0f;

void Engine::Setup(){
    mainCamera = new Camera();

    light = new Light();



    matProgram = new ShaderProgram("Content/Shaders/Lighting/Shaded.frag", "Content/Shaders/Lighting/Shaded.vert");

    g2 = new Plane(300, 300);
    g2->SetRotation(Vector3{0.0f, 0.0f, 0.0f});
    g2->SetScale(Vector3{10.0f, 1.0, 10.0f});

    object = new SceneObject();
    object->position = Vector3{0, 5, 0};

    vector<Vertex> mesh = unpackOBJ("Content/Models/teapot_smooth.obj");
    object2 = new SceneObject(mesh);
    object2->position = Vector3{2.5, 2.5, 2.5};
    object2->scale = Vector3{5, 5, 5};

    l = new SceneObject();
    l->position = Vector3{light->position.x, light->position.y, light->position.z};
    l->scale = Vector3{0.5, 0.5, 0.5};

    AddObjectToScene(matProgram, g2); //Add to a map in the class.
    AddObjectToScene(matProgram, object);
    AddObjectToScene(matProgram, object2);
    AddObjectToScene(matProgram, l);




    //glEnable(GL_CULL_FACE);




}


void Engine::Update() {
    t+=0.01;
    //object->position = Vector3{ 5.0f * cos(t), 2.0f + 2.0f * sin(t) , 5.0f * sin(t)};
    light->position = glm::vec3(10.f * cos(t), 5.0f, 10.f * sin(t));
    l->position = Vector3{light->position.x, light->position.y, light->position.z};

}



void Engine::Draw() {

    //glCullFace(GL_FRONT);
    light->Start(); //We 'start' the light which configures the shader program as well as any uniforms
    g2->Draw(light->Program); //We then draw objects.
    object->Draw(light->Program);
    object2->Draw(light->Program);
    light->Stop(); // Resets the rendering target to openGL default.




    //glCullFace(GL_BACK);

//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Does not seem to have any effect.
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);  //lines cause the scene to stop rendering correctly, about a forth of the size until I resize the window (Possible due to working on a retina display.
    DrawScene(matProgram); //Draws all objects mapped to this shader program object. Look in header file its pretty simple.

}


// Basic

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