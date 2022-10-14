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
        ~Camera();


        glm::mat4 getView() { return m_View; }
        glm::mat4 getProjection() { return m_Projection; }

    private:
        glm::mat4 m_View;
        glm::mat4 m_Projection;


    };
};

#endif
