#include "lnpch.h"
#include "Camera.h"


#include <GLFW/glfw3.h>

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



    Camera::Camera(glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f), float _yaw = YAW, float _pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM)
    {
        Position = _position;
        WorldUp = _up;
        m_Yaw = _yaw;
        m_Pitch = _pitch;
        UpdateCameraVectors();
    }

    Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        m_Yaw = yaw;
        m_Pitch = pitch;
        UpdateCameraVectors();
    }

    Camera::~Camera()
    {
    }


    glm::mat4 Camera::getView()
    {
        return m_View;
    }

    glm::mat4 Camera::getProjection()
    {
        return m_Projection;
    }

    void Camera::setAspectRatio(float aspectRatio)
    {
        m_AspectRatio = aspectRatio;
        if (m_type==CameraType::PERSPECTIVE)
            m_Projection = glm::perspective(glm::radians(m_Fov), aspectRatio, m_zNear, m_zFar);
    }

    void Camera::setResolution(int width, int height)
    {
        m_AspectRatio = width / (float)height;

        if (m_type == CameraType::PERSPECTIVE)
            m_Projection = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_zNear, m_zFar);
        else if (m_type == CameraType::ORTHOGRAPHIC)
            m_Projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f);
    }

    void Camera::setFOV(float fov)
    {
        m_Fov = fov;

        if (m_type == CameraType::PERSPECTIVE)
            m_Projection = glm::perspective(glm::radians(fov), m_AspectRatio, m_zNear, m_zFar);
    }

    void Camera::SetPerspective(float fov, float aspectRatio, float nearDistance, float farDistance)
    {
        m_type = CameraType::PERSPECTIVE;

        m_Projection = glm::perspective(glm::radians(m_Fov), aspectRatio, nearDistance, farDistance);

        m_AspectRatio = aspectRatio;
        m_zNear = nearDistance;
        m_zFar = farDistance;
    }

    void Camera::SetOrthographic(int width, int height, float nearDistance, float farDistance)
    {
        m_type = CameraType::ORTHOGRAPHIC;

        m_Projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, nearDistance, farDistance);

        m_AspectRatio = width / (float)height;
        m_zNear = nearDistance;
        m_zFar = farDistance;
    }

    void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
    {
        float x, y;
        x = xoffset * m_MouseSensitivity;
        y = yoffset * m_MouseSensitivity;

        m_Yaw += x;
        m_Pitch += y;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (m_Pitch > 89.0f)
                m_Pitch = 89.0f;
            if (m_Pitch < -89.0f)
                m_Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        UpdateCameraVectors();
    }

    void Camera::ProcessMouseScroll(float yOffset)
    {
        m_Zoom -= (float)yOffset;
        if (m_Zoom < 1.0f)
            m_Zoom = 1.0f;
        if (m_Zoom > 45.0f)
            m_Zoom = 45.0f;
    }

    void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = m_MovementSpeed * deltaTime;
        if (direction == FREE_LOOK_UP)
            Position += Front * velocity;
        if (direction == FREE_LOOK_DOWN)
            Position -= Front * velocity;
        if (direction == FREE_LOOK_LEFT)
            Position -= Right * velocity;
        if (direction == FREE_LOOK_RIGHT)
            Position += Right * velocity;

        UpdateCameraVectors();
    }

    void Camera::UpdateCameraVectors()
    {

        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        front.y = sin(glm::radians(m_Pitch));
        front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));

        m_View = glm::lookAt(Position, Position + Front, Up);

    }

}