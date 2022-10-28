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

#include "Lanna/Input.h"
#include "Lanna/KeyCodes.h"

CameraComponent::CameraComponent(TransformComponent* t)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseWheelSensitivity(SENSITIVITY), m_Zoom(ZOOM), Component(Component::Type::CAMERA)
{
    Position = &t->m_Position;
    WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    Rotation = &t->m_Rotation;
    UpdateCameraVectorsFromEulerAngles();
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
        ImGui::InputFloat("mouse sens", &m_MouseWheelSensitivity, SENSITIVITY, 0.0f, "%.5f");


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

    updateView();
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

    m_Fov = fov;

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
    if (Lanna::Input::IsKeyPressed(LN_KEY_LEFT_ALT))
    {
        if (Lanna::Input::IsKeyPressed(LN_KEY_LEFT_SHIFT))
            speedMul = 2.0f;
        else speedMul = 1.0f;

        ImGuiIO& io = ImGui::GetIO();

        if (io.MouseDown[0]) Orbit(xoffset, yoffset);
        if (io.MouseDown[2]) Move(xoffset, yoffset);
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    UpdateCameraVectorsFromEulerAngles();
}

void CameraComponent::ProcessMouseScroll(float yOffset)
{
    
    if (Lanna::Input::IsKeyPressed(LN_KEY_LEFT_ALT))
    {
        if (Lanna::Input::IsKeyPressed(LN_KEY_LEFT_SHIFT))
            speedMul = 2.0f;
        else speedMul = 1.0f;
        float lastZoom = m_Zoom;
        m_Zoom -= yOffset * m_MouseWheelSensitivity * speedMul;
        if (m_Zoom < 0.5f)m_Zoom = 0.5f;
        Front=UnitaryVector(Front);
        
        *Position -= Front * (lastZoom-m_Zoom);
        UpdateCameraVectorsFromEulerAngles();
    }
    

}

void CameraComponent::LookAt(glm::vec3 spot)
{

    m_View = glm::lookAt(*Position + spot, *Position, Up);
    Front = spot - *Position;
    UpdateCameraVectorsFromCameraDirection();
}

void CameraComponent::updateView()
{
    m_View = glm::lookAt(*Position, *Position + Front, Up);
}

void CameraComponent::UpdateCameraVectorsFromEulerAngles()
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

void CameraComponent::UpdateCameraVectorsFromCameraDirection()
{
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up= glm::normalize(glm::cross(Right, Front));

    Rotation->x = glm::degrees(atan(Up.z / Up.y));
    Rotation->y = glm::degrees(atan(Front.z / Front.x));
    Rotation->z = 0;
}

void CameraComponent::Move(float xoffset, float yoffset)
{
    *Position += Right * xoffset * m_MovementSpeed * speedMul;
    *Position += Up * yoffset * m_MovementSpeed * speedMul;
    UpdateCameraVectorsFromEulerAngles();
}

void CameraComponent::Orbit(float xoffset, float yoffset)
{

    *Position += Right * xoffset * m_MovementSpeed * speedMul;
    *Position += Up * yoffset * m_MovementSpeed * speedMul;
    
    Front -= Right * xoffset * m_MovementSpeed * speedMul;
    Front -= Up * yoffset * m_MovementSpeed * speedMul;
    UpdateCameraVectorsFromCameraDirection();
}

glm::vec3 CameraComponent::UnitaryVector(glm::vec3 vec)
{
    glm::vec3 unitary = vec;
    float multiplier = 1/glm::distance(vec, glm::vec3(0.0f, 0.0f, 0.0f));
    unitary *= multiplier;
    return unitary;
}

