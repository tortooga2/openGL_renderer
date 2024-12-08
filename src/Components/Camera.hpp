//
// Created by Chase Nagle on 11/25/24.
//

#ifndef OPENGLPROJECT_CAMERA_HPP
#define OPENGLPROJECT_CAMERA_HPP

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Globals.hpp"
#include "./ShaderProgram.hpp"

// Enum for camera movements
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // Euler angles
    float Yaw;
    float Pitch;


    float AspectRatio;

public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, -3.0f), int width = 750, int height = 750) {
        Position = position;
        WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        Yaw = 90.0f;
        Pitch = 0.0f;

        UpdateAspectRatio(width, height);
        updateCameraVectors();
    }



    Camera(Vector3 pos, int width, int height){
        Position = glm::vec3(pos.x, pos.y, pos.z);
        WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        Yaw = 90.0f;
        Pitch = 0.0f;

        UpdateAspectRatio(width, height);
        updateCameraVectors();
    };


    // Returns the view matrix calculated using Euler angles and lookAt matrix
    glm::mat4 GetViewMatrix() {
        return glm::lookAt(Position, Position + Front, Up);
    };
    glm::mat4 GetProjMatrix() {
        return glm::perspective(glm::radians(45.0f), AspectRatio , 0.001f, 1000.0f);
    };

    void Use(ShaderProgram *program) {
        glm::mat4 ViewMatrix = GetViewMatrix();
        glm::mat4 ProjMatrix = GetProjMatrix();

        program->setUniformMat4x4("ViewMatrix", ViewMatrix);
        program->setUniformMat4x4("ProjMatrix", ProjMatrix);
    }

    void ChangePos(Vector3 pos){
        Position += glm::vec3(pos.x, pos.y, pos.z) ;
    }







    // Get camera position
    glm::vec3 GetPosition() const {
        return Position;
    }




public:
    // Calculate the front vector from the Camera's Euler angles
    void updateCameraVectors() {
        // Calculate new front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);

        // Recalculate Right and Up vectors
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up    = glm::normalize(glm::cross(Right, Front));
    }

    void UpdateAspectRatio(float ScreenWidth, float ScreenHeight){
        AspectRatio = ScreenWidth / ScreenHeight;
    }
};







#endif //OPENGLPROJECT_CAMERA_HPP
