#include "lnpch.h"
#include "Camera.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>

#include <gl/GL.h>


// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 0.0001f;
const float SENSITIVITY = 0.0001f;
const float ZOOM = 45.0f;

namespace Lanna {
    Camera::Camera() : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(0.0f, 0.0f, 0.0f);
        WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        yaw = 0;
        pitch = 0;
        roll = 0;
        matWorldToCam = new float[4 * 4];
        matCamToWorld = new float[4 * 4];

        updateCameraVectors();
    }
    // constructor with vectors
    Camera::Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float _yaw = YAW, float _pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        yaw = _yaw;
        pitch = _pitch;
        updateCameraVectors();
    }

    Camera::~Camera()
    {
        delete[] matWorldToCam;
        delete[] matCamToWorld;
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 Camera::GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
        GenerateMats();
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        yaw += xoffset;
        pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        GenerateMats();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void Camera::ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

    void Camera::PrintTiangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
    {
        glm::vec3 u1 = WorldToCam(v1);
        glm::vec3 u2 = WorldToCam(v2);
        glm::vec3 u3 = WorldToCam(v3);



        glBegin(GL_TRIANGLES);

        glVertex3f(u1.x, u1.y, u1.z);
        glVertex3f(u2.x, u2.y, u2.z);
        glVertex3f(u3.x, u3.y, u3.z);
        glEnd();
    }

    // calculates the front vector from the Camera's (updated) Euler Angles
    void Camera::updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));





    }


    void Camera::GenerateMats()
    {
        float* m = matWorldToCam;
        float* m2 = matWorldToCam;

        m[0 * 4 + 0] = m2[0 * 4 + 0] = cos(pitch) * cos(yaw);
        m[1 * 4 + 0] = m2[0 * 4 + 1] = cos(pitch) * sin(yaw);
        m[2 * 4 + 0] = m2[0 * 4 + 2] = -sin(pitch);

        m[0 * 4 + 1] = m2[1 * 4 + 0] = cos(yaw) * sin(pitch) * sin(roll) - cos(roll) * sin(yaw);
        m[1 * 4 + 1] = m2[1 * 4 + 1] = sin(yaw) * sin(pitch) * sin(roll) + cos(roll) * cos(yaw);
        m[2 * 4 + 1] = m2[1 * 4 + 2] = cos(pitch) * sin(roll);

        m[0 * 4 + 2] = m2[2 * 4 + 0]=cos(yaw) * cos(roll) * sin(pitch) + sin(yaw) * sin(roll);
        m[1 * 4 + 2] = m2[2 * 4 + 1] = sin(yaw) * sin(pitch) * cos(roll) - cos(yaw) * sin(roll);
        m[2 * 4 + 2] = m2[2 * 4 + 2] = cos(pitch) * cos(roll);


        m[0 * 4 + 3] = -Position.x;
        m[1 * 4 + 3] = -Position.y;
        m[2 * 4 + 3] = -Position.z;

        m2[0 * 4 + 3] = Position.x;
        m2[1 * 4 + 3] = Position.y;
        m2[2 * 4 + 3] = Position.z;

        m[3 * 4 + 0] = m2[3 * 4 + 0] = 0;
        m[3 * 4 + 1] = m2[3 * 4 + 1] = 0;
        m[3 * 4 + 2] = m2[3 * 4 + 2] = 0;
        m[3 * 4 + 3] = m2[3 * 4 + 2] = 1;
    }

    glm::vec3 Camera::WorldToCam(glm::vec3 vec)
    {
        float res[4] = { 0 };
        float v[4] = { vec.x,vec.y,vec.z,1 };

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                res[i] += matWorldToCam[i * 4 + j] * v[j];
            }
        }

        return glm::vec3(res[0],res[1],res[2]);
    }

    glm::vec3 Camera::CamToWorld(glm::vec3 vec)
    {
        float res[4] = { 0 };
        float v[4] = { vec.x,vec.y,vec.z,1 };

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                res[i] += matCamToWorld[i * 4 + j] * v[j];
            }
        }

        return glm::vec3(res[0], res[1], res[2]);
    }

}