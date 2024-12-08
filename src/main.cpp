

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

#include "./Components/mainEngine.hpp"



void framebuffer_size_callback(GLFWwindow* window, int width, int height);


// settings
const unsigned int SCR_WIDTH = 750;
const unsigned int SCR_HEIGHT = 750;




Engine *engine;





void processInput(GLFWwindow *window){

}




int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGLProject", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwWindowHint(GLFW_DEPTH_BITS, 24);  // Request a depth buffer with 24 bits

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);


    engine = new Engine(window);
    engine->Setup();

    float lastFrameTime = glfwGetTime();
    float dt;

    while (!glfwWindowShouldClose(window))
    {

        dt = (float)glfwGetTime() - lastFrameTime;
        engine->GetTimeDelta(dt);
        lastFrameTime = (float)glfwGetTime();


        processInput(window);
        glClearColor(0.8f, 0.7f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        engine->KeyboardEvent();
        engine->Update();
        engine->Draw();


        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();

    

    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.

    glViewport(0, 0, width, height);
    engine->OnResize(width, height);



}