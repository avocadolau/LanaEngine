#include "lnpch.h"
#include "CameraComponent.h"
#include "Lanna/GameObject/Component.h"
#include "TransformComponent.h"

#include <imgui.h>

#include <glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>

#include <gl/GL.h>

#include "TransformComponent.h"


CameraComponent::CameraComponent(TransformComponent* t)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM), Component(Component::Type::CAMERA)
{
    Position = &t->m_Position;
    WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    Rotation = &t->m_Rotation;
    m_Yaw = YAW;
    m_Pitch = PITCH;  
    UpdateCameraVectors();
}

//CameraComponent::CameraComponent(glm::vec3 _position, glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f), float _yaw = YAW, float _pitch = PITCH)
//	: Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM), Component(Component::Type::CAMERA)
//{
//	Position =_position;
//	WorldUp = _up;
//	m_Yaw = _yaw;
//	m_Pitch = _pitch;
//	UpdateCameraVectors();
//}
//
//CameraComponent::CameraComponent(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
//	: Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM), Component(Component::Type::CAMERA)
//{
//	Position =glm::vec3(posX, posY, posZ);
//	WorldUp = glm::vec3(upX, upY, upZ);
//	m_Yaw = yaw;
//	m_Pitch = pitch;
//	UpdateCameraVectors();
//}

CameraComponent::~CameraComponent()
{

}

void CameraComponent::Use()
{
    
}

void CameraComponent::ImGuiDraw()
{
	if (ImGui::TreeNode("Camera"))
	{
        

        //ImGui::DragFloat("##value", &m_Position.x, 1.0f);

        ImGui::Text("Position");
        float val = Position->x;
        ImGui::Text("x ");
        ImGui::SameLine();
        ImGui::Text(std::to_string(val).c_str());
        val = Position->y;
        ImGui::Text("y ");
        ImGui::SameLine();
        ImGui::Text(std::to_string(val).c_str());
        val = Position->z;
        ImGui::Text("z ");
        ImGui::SameLine();
        ImGui::Text(std::to_string(val).c_str());


        ImGui::BeginTable("uwu", 2, !ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable|!ImGuiTableFlags_Borders|ImGuiTableFlags_NoBordersInBodyUntilResize);
        ImGui::TableNextRow();

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("Zoom");
        ImGui::TableSetColumnIndex(1);
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::InputFloat("zoom", &m_Zoom, 1.0f, 0.0f, "%.1f");
      
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("Fov");
        ImGui::TableSetColumnIndex(1);
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::InputFloat("fov", &m_Fov, 1.0f, 0.0f, "%.1f");

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("Near");
        ImGui::TableSetColumnIndex(1);
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::InputFloat("near", &m_zNear, 0.1f, 0.0f, "%.1f");

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("Far");
        ImGui::TableSetColumnIndex(1);
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::InputFloat("far", &m_zFar, 1.0f, 0.0f, "%.1f");

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("Movement Speed");
        ImGui::TableSetColumnIndex(1);
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::InputFloat("mov speed", &m_MovementSpeed, SPEED, 0.0f, "%.5f");

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("MouseSensitivity");
        ImGui::TableSetColumnIndex(1);
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::InputFloat("mouse sens", &m_MouseSensitivity, SENSITIVITY, 0.0f, "%.5f");


        ImGui::EndTable();


        ImGui::TreePop();
	}
}

glm::mat4 CameraComponent::getView()
{
	return m_View;
}

glm::mat4 CameraComponent::getProjection()
{
    return m_Projection;
}

void CameraComponent::setAspectRatio(float aspectRatio)
{
    m_AspectRatio = aspectRatio;
    if (m_type == CameraType::PERSPECTIVE)
        m_Projection = glm::perspective(glm::radians(m_Fov), aspectRatio, m_zNear, m_zFar);
}

void CameraComponent::setResolution(int width, int height)
{
    m_AspectRatio = width / (float)height;

    if (m_type == CameraType::PERSPECTIVE)
        m_Projection = glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_zNear, m_zFar);
    else if (m_type == CameraType::ORTHOGRAPHIC)
        m_Projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f);
}

void CameraComponent::setPosition(glm::vec3 pos)
{
    *Position = pos;
}

void CameraComponent::setFOV(float fov)
{
    m_Fov = fov;

    if (m_type == CameraType::PERSPECTIVE)
        m_Projection = glm::perspective(glm::radians(fov), m_AspectRatio, m_zNear, m_zFar);
}

void CameraComponent::SetPerspective(float fov, float aspectRatio, float nearDistance, float farDistance)
{
    m_type = CameraType::PERSPECTIVE;

    m_Projection = glm::perspective(glm::radians(m_Fov), aspectRatio, nearDistance, farDistance);

    m_AspectRatio = aspectRatio;
    m_zNear = nearDistance;
    m_zFar = farDistance;
}

void CameraComponent::SetOrthographic(int width, int height, float nearDistance, float farDistance)
{
    m_type = CameraType::ORTHOGRAPHIC;

    m_Projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, nearDistance, farDistance);

    m_AspectRatio = width / (float)height;
    m_zNear = nearDistance;
    m_zFar = farDistance;
}

void CameraComponent::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
{
    float x, y;
    x = xoffset * m_MouseSensitivity;
    y = yoffset * m_MouseSensitivity;

    Rotation->x += x;
    Rotation->y += y;
    /*m_Yaw += x;
    m_Pitch += y;*/

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Rotation->x > 89.0f)
            Rotation->x = 89.0f;
        if (Rotation->y < -89.0f)
            Rotation->y = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    UpdateCameraVectors();
}

void CameraComponent::ProcessMouseScroll(float yOffset)
{
    m_Zoom -= (float)yOffset;
    if (m_Zoom < 1.0f)
        m_Zoom = 1.0f;
    if (m_Zoom > 45.0f)
        m_Zoom = 45.0f;
}

void CameraComponent::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = m_MovementSpeed * deltaTime;
    if (direction == FREE_LOOK_UP)
        *Position += Front * velocity;
    if (direction == FREE_LOOK_DOWN)
        *Position -= Front * velocity;
    if (direction == FREE_LOOK_LEFT)
        *Position -= Right * velocity;
    if (direction == FREE_LOOK_RIGHT)
        *Position += Right * velocity;

    UpdateCameraVectors();
}

void CameraComponent::LookAt(glm::vec3 spot)
{
    glm::vec3 vecToSpot = spot - *Position;


    Front = spot;
    UpdateCameraVectors();
}

void CameraComponent::UpdateCameraVectors()
{

    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Rotation->y)) * cos(glm::radians(Rotation->x));
    front.y = sin(glm::radians(Rotation->x));
    front.z = sin(glm::radians(Rotation->y)) * cos(glm::radians(Rotation->x));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));

    m_View = glm::lookAt(*Position, *Position + Front, Up);

}