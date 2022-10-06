#pragma once


#ifndef CAMERA_H
#define CAMERA_H
#include "lnpch.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>

namespace Lanna
{

    // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    // An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
    class Camera
    {
    public:
        
        Camera();
        Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
        ~Camera();

        glm::mat4 GetViewMatrix();
        void ProcessKeyboard(Camera_Movement direction, float deltaTime);
        void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch);
        void ProcessMouseScroll(float yoffset);

        void PrintTiangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

    private:
        void updateCameraVectors();

        void GenerateMats();
        glm::vec3 WorldToCam(glm::vec3 vec);
        glm::vec3 CamToWorld(glm::vec3 vec);
        
    public:
        // camera Attributes
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;
        // euler Angles
        float yaw;
        float pitch;
        float roll;
        // camera options
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;


        // own camera
        float* matWorldToCam;
        float* matCamToWorld;



    };
};

#endif
