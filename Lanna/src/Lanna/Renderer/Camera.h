#pragma once


#ifndef CAMERA_H
#define CAMERA_H
#include "lnpch.h"

#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>

namespace Lanna
{
    enum class CameraType {
        NONE,
        ORTHOGRAPHIC,
        PERSPECTIVE
    };
    enum Camera_Movement {
        ZOOM_IN,
        ZOOM_OUT,
        ORBIT,
        FOCUS,
        FREE_LOOK_UP,
        FREE_LOOK_DOWN,
        FREE_LOOK_RIGHT,
        FREE_LOOK_LEFT
    };
    // An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
    class Camera
    {
    public:
        Camera(glm::vec3 _position, glm::vec3 _up, float _yaw, float _pitch);
        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

        ~Camera();

        glm::mat4 getView();
        glm::mat4 getProjection();

        void setAspectRatio(float aspectRatio);
        float getAspectRatio() { return m_AspectRatio; }
        void setResolution(int width, int height);

        void setFOV(float fov);
        float getFOV() { return m_Fov; }

        void SetPerspective(float fov, float aspectRatio, float nearDistance = 0.1f, float farDistance = 100.0f);
        void SetOrthographic(int width, int height, float nearDistance = 0.1f, float farDistance = 100.0f);

        void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch);
        void ProcessMouseScroll(float yOffset);
        void ProcessKeyboard(Camera_Movement direction, float deltaTime);

        void SetPosition(glm::vec3 pos) { Position = pos; }
        void LookAt(const glm::vec3 pos);
    private:
        void UpdateCameraVectors();
    
    private:

        CameraType m_type;

        // camera Attributes
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;

        // euler Angles
        float m_Yaw;
        float m_Pitch;
        // camera options
        float m_MovementSpeed;
        float m_MouseSensitivity;
        float m_Zoom;
        float m_Fov = 45.0f;
        float m_zNear = 0.1f;
        float m_zFar = 100.0f;
        float m_AspectRatio;


        // matrices
        glm::mat4 m_View;
        glm::mat4 m_Projection;


    };
};

#endif
