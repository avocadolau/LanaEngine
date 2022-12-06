#pragma once
#include "Lanna/GameObject/Component.h"
#include "TransformComponent.h"
#include "Lanna/Resources/Framebuffer.h"

#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float ZOOM = 45.0f;

namespace Lanna
{
    enum class CameraType {
        NONE,
        ORTHOGRAPHIC,
        PERSPECTIVE
    };

    class CameraComponent : public Component
    {
    public:
        CameraComponent(CameraComponent* copy, TransformComponent* t);
        CameraComponent(TransformComponent* t);
        /*CameraComponent(glm::vec3 _position, glm::vec3 _up, float _yaw, float _pitch);
        CameraComponent(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);*/
        ~CameraComponent();

        void Use() override;
        void ImGuiDraw() override;

        glm::mat4 getView();
        glm::mat4 getProjection();

        void setAspectRatio(float aspectRatio);
        float getAspectRatio() { return m_AspectRatio; }
        void setResolution(int width, int height);

        void setPosition(glm::vec3 pos);
        void UpdateRotation();

        void setFOV(float fov);
        float getFOV() { return m_Fov; }

        void SetPerspective(float fov, float aspectRatio, float nearDistance = 0.1f, float farDistance = 100.0f);
        void SetOrthographic(int width, int height, float nearDistance = 0.1f, float farDistance = 100.0f);

        void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch);
        void ProcessMouseScroll(float yOffset);

        void LookAt(glm::vec3 spot);

        void updateView();
         
        void setFront(const glm::vec3 front);
    private:
        /*void UpdateCameraVectorsFromEulerAngles();*/
        void UpdateCameraVectorsFromCameraSpot();

        void Move(float xoffset, float yoffset);
        void Orbit(float xoffset, float yoffset);
        void FreeLookAround(float xoffset, float yoffset);

        glm::vec3 UnitaryVector(glm::vec3 vec);
    private:
        CameraType m_type;

        // camera Attributes
        glm::vec3* Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;

        // euler Angles
        glm::vec3* Rotation;
        float m_Yaw = 0.0f;
        float m_Pitch = 0.0f;
        // camera options
        float m_MovementSpeed;
        float m_FreeLookSpeed;
        float m_ZoomSpeed;
        float m_OrbitSpeed;
        float m_Fov = 45.0f;
        float m_zNear = 0.1f;
        float m_zFar = 100.0f;
        float m_AspectRatio;

        float speedMul = 1.0f;

        // matrices
        glm::mat4 m_View;
        glm::mat4 m_Projection;

    private:
        glm::vec3 m_WorldSpot;
        float lastPitch;    //x
        float lastYaw;      //y
        float distance = 10.0f;
        glm::vec2 lastpos;
        bool freelookaround = false;

        glm::vec2  resolution;

    public:

        Framebuffer m_Framebuffer;
    };
}