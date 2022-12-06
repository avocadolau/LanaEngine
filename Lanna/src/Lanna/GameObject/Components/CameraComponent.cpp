#include "lnpch.h"
#include "CameraComponent.h"
#include "Lanna/GameObject/Component.h"
#include "TransformComponent.h"

#include <imgui.h>

#include <glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>
#include <vector>

#include <gl/GL.h>

#include "TransformComponent.h"

#include "Lanna/Input.h"
#include "Lanna/KeyCodes.h"
#include "Lanna/EntityManager.h"
#include "Lanna/Application.h"

namespace Lanna
{
    CameraComponent::CameraComponent(CameraComponent* copy, TransformComponent*t) :Component(Component::Type::CAMERA)
    {
        Lanna::Window& window = Lanna::Application::Get().GetWindow();
        resolution = { window.GetHeight(), window.GetHeight() };

        m_Framebuffer.Init(resolution.x, resolution.y);

        Position = &t->m_Position;
        WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        Rotation = &t->m_Rotation;
        lastPitch = Rotation->x;
        lastYaw = Rotation->y;

        m_WorldSpot = copy->m_WorldSpot;
        m_MovementSpeed = 0.003f;
        m_OrbitSpeed = 0.001f;
        m_ZoomSpeed = 0.00001f;
        m_FreeLookSpeed = 0.001f;
        UpdateCameraVectorsFromCameraSpot();
    }
    CameraComponent::CameraComponent(TransformComponent* t)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), Component(Component::Type::CAMERA)
    {
        Lanna::Window& window = Lanna::Application::Get().GetWindow();
        resolution = { window.GetHeight(), window.GetHeight() };

        m_Framebuffer.Init(resolution.x, resolution.y);

        Position = &t->m_Position;
        WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        Rotation = &t->m_Rotation;
        lastPitch = Rotation->x;
        lastYaw = Rotation->y;
        m_WorldSpot = (glm::vec3(0.0f, 0.0f, -10.0f) - *Position);
        m_MovementSpeed = 0.003f;
        m_OrbitSpeed = 0.001f;
        m_ZoomSpeed = 0.00001f;
        m_FreeLookSpeed = 0.001f;
        UpdateCameraVectorsFromCameraSpot();
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
        UpdateRotation();
        if (Lanna::Input::IsKeyPressed(LN_KEY_F))
        {
            GameObject* active = LN_ENTITY_MAN->GetActiveEntitiy();
            LookAt(active->m_Transform->m_Position);
        }

        ImGuiIO& io = ImGui::GetIO();
        if (io.MouseDown[1])
        {
            float speedVel = speedMul;
            if (Lanna::Input::IsKeyPressed(LN_KEY_LEFT_SHIFT))
                speedVel = 2.0f;

            if (Lanna::Input::IsKeyPressed(LN_KEY_W))
            {
                glm::vec3 _front = UnitaryVector(Front);
                *Position += _front * m_MovementSpeed * speedVel * io.Framerate;
                m_WorldSpot += _front * m_MovementSpeed * speedVel * io.Framerate;
                UpdateCameraVectorsFromCameraSpot();
            }
            if (Lanna::Input::IsKeyPressed(LN_KEY_S))
            {
                glm::vec3 _front = UnitaryVector(Front);
                *Position -= _front * m_MovementSpeed * speedVel * io.Framerate;
                m_WorldSpot -= _front * m_MovementSpeed * speedVel * io.Framerate;
                UpdateCameraVectorsFromCameraSpot();
            }
            if (Lanna::Input::IsKeyPressed(LN_KEY_A))
            {
                glm::vec3 _right = UnitaryVector(Right);
                *Position -= _right * m_MovementSpeed * speedVel * io.Framerate;
                m_WorldSpot -= _right * m_MovementSpeed * speedVel * io.Framerate;
                UpdateCameraVectorsFromCameraSpot();
            }
            if (Lanna::Input::IsKeyPressed(LN_KEY_D))
            {
                glm::vec3 _right = UnitaryVector(Right);
                *Position += _right * m_MovementSpeed * speedVel * io.Framerate;
                m_WorldSpot += _right * m_MovementSpeed * speedVel * io.Framerate;
                UpdateCameraVectorsFromCameraSpot();
            }
        }
    }

    void CameraComponent::ImGuiDraw()
    {
        UpdateRotation();
        UpdateCameraVectorsFromCameraSpot();
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


            ImGui::Text("Spot");
            val = m_WorldSpot.x;
            ImGui::Text("x ");
            ImGui::SameLine();
            ImGui::Text(std::to_string(val).c_str());
            val = m_WorldSpot.y;
            ImGui::Text("y ");
            ImGui::SameLine();
            ImGui::Text(std::to_string(val).c_str());
            val = m_WorldSpot.z;
            ImGui::Text("z ");
            ImGui::SameLine();
            ImGui::Text(std::to_string(val).c_str());


            ImGui::Text("Spot");
            ImGui::Text("x");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::DragFloat("pos  x", &m_WorldSpot.x, 0.01f);
            ImGui::Text("y");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::DragFloat("posy y", &m_WorldSpot.y, 0.01f);
            ImGui::Text("z");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::DragFloat("pos z", &m_WorldSpot.z, 0.01f);


            ImGui::BeginTable("uwu", 2, !ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable | !ImGuiTableFlags_Borders | ImGuiTableFlags_NoBordersInBodyUntilResize);
            ImGui::TableNextRow();


            /*ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Zoom");
            ImGui::TableSetColumnIndex(1);
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::DragFloat("zoom", &m_Zoom, 0.01f, 0, 1000000, "%.1f");*/

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Fov");
            ImGui::TableSetColumnIndex(1);
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::DragFloat("fov", &m_Fov, 1.0f);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Near");
            ImGui::TableSetColumnIndex(1);
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::DragFloat("near", &m_zNear, 0.1f, 0.0f);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Far");
            ImGui::TableSetColumnIndex(1);
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::DragFloat("far", &m_zFar, 1.0f, 0.0f);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Movement Speed");
            ImGui::TableSetColumnIndex(1);
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::DragFloat("mov speed", &m_MovementSpeed, m_MovementSpeed, 0.0f);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Orbit Speed");
            ImGui::TableSetColumnIndex(1);
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::DragFloat("Orbit speed", &m_OrbitSpeed, m_OrbitSpeed, 0.0f);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Zoom Speed");
            ImGui::TableSetColumnIndex(1);
            ImGui::SetNextItemWidth(-FLT_MIN);
            ImGui::DragFloat("Zoom speed", &m_ZoomSpeed, m_ZoomSpeed, 0.0f);


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
        Front = m_WorldSpot - *Position;

        UpdateCameraVectorsFromCameraSpot();
    }

    void CameraComponent::UpdateRotation()
    {
        if (lastPitch != Rotation->x)
        {
            glm::vec3 nSpot = m_WorldSpot + *Position;
            nSpot = glm::rotate(nSpot, Rotation->x - lastPitch, Right);
            nSpot = UnitaryVector(nSpot) * distance;
            m_WorldSpot = nSpot - *Position;
            UpdateCameraVectorsFromCameraSpot();
        }
        if (lastYaw != Rotation->y)
        {
            glm::vec3 nSpot = m_WorldSpot + *Position;
            nSpot = glm::rotate(nSpot, Rotation->y - lastYaw, Up);
            nSpot = UnitaryVector(nSpot) * distance;
            m_WorldSpot = nSpot - *Position;
            UpdateCameraVectorsFromCameraSpot();
        }
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

    void CameraComponent::ProcessMouseMovement(float x, float y, bool constrainPitch = true)
    {
        if (Lanna::Input::IsMouseButtonPressed(1))
            FreeLookAround(x - lastpos.x, y - lastpos.y);


        if (Lanna::Input::IsKeyPressed(LN_KEY_LEFT_ALT))
        {
            if (Lanna::Input::IsKeyPressed(LN_KEY_LEFT_SHIFT))
                speedMul = 2.0f;
            else speedMul = 1.0f;

            ImGuiIO& io = ImGui::GetIO();
            
            if (Lanna::Input::IsMouseButtonPressed(0)) Orbit(x - lastpos.x, y - lastpos.y);
            if (Lanna::Input::IsMouseButtonPressed(2)) Move(x - lastpos.x, y - lastpos.y);
            
        }
        lastpos.x = x;
        lastpos.y = y;
    }

    void CameraComponent::ProcessMouseScroll(float yOffset)
    {
        
        if (Lanna::Input::IsKeyPressed(LN_KEY_LEFT_ALT))
        {
            if (Lanna::Input::IsKeyPressed(LN_KEY_LEFT_SHIFT))
                speedMul = 2.0f;
            else speedMul = 1.0f;

            float mul = 10000.0f;
            glm::vec3 front = UnitaryVector(Front);
            *Position += front * yOffset * m_ZoomSpeed * speedMul * mul;
            m_WorldSpot -= front * yOffset * m_ZoomSpeed * speedMul * mul;
            UpdateCameraVectorsFromCameraSpot();
        }


    }

    void CameraComponent::LookAt(glm::vec3 spot)
    {
        m_WorldSpot = spot;
        m_View = glm::lookAt(*Position + m_WorldSpot, *Position, Up);
        UpdateCameraVectorsFromCameraSpot();
    }

    void CameraComponent::updateView()
    {
        m_View = glm::lookAt(*Position, *Position + m_WorldSpot, Up);
    }

    void CameraComponent::setFront(const glm::vec3 front)
    {
        Front = front;
        updateView();
    }

    //void CameraComponent::UpdateCameraVectorsFromEulerAngles()
    //{
    //    // calculate the new Front vector
    //    glm::vec3 front;
    //    front.x = cos(glm::radians(Rotation->y)) * cos(glm::radians(Rotation->x));
    //    front.y = sin(glm::radians(Rotation->x));
    //    front.z = sin(glm::radians(Rotation->y)) * cos(glm::radians(Rotation->x));
    //    Front = glm::normalize(front);
    //    // also re-calculate the Right and Up vector
    //    Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    //    Up = glm::normalize(glm::cross(Right, Front));
    //
    //
    //    float distance = glm::distance(m_WorldSpot, *Position);
    //    front = UnitaryVector(Front);
    //    m_WorldSpot = front * distance - *Position;
    //
    //    m_View = glm::lookAt(*Position, *Position + Front, Up);
    //
    //}

    void CameraComponent::UpdateCameraVectorsFromCameraSpot()
    {
        /*Front = glm::normalize(m_WorldSpot - *Position);
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up= glm::normalize(glm::cross(Right, Front));*/
        Front = m_WorldSpot - *Position;
        Right = glm::cross(Front, WorldUp);
        Up = glm::cross(Right, Front);

        Rotation->x = glm::degrees(atan(Up.z / Up.y));
        Rotation->y = glm::degrees(atan(Front.z / Front.x));
        Rotation->z = 0;

        lastPitch = Rotation->x;
        lastYaw = Rotation->y;
        distance = glm::distance(*Position, m_WorldSpot);
        m_View = glm::lookAt(*Position, *Position + Front, Up);
    }

    void CameraComponent::Move(float xoffset, float yoffset)
    {
        glm::vec3 _right = UnitaryVector(Right);
        glm::vec3 _up = UnitaryVector(Up);
        *Position += _right * -xoffset * m_MovementSpeed * speedMul;
        *Position += _up * yoffset * m_MovementSpeed * speedMul;
        m_WorldSpot += _right * -xoffset * m_MovementSpeed * speedMul;
        m_WorldSpot += _up * yoffset * m_MovementSpeed * speedMul;
        UpdateCameraVectorsFromCameraSpot();
    }

    void CameraComponent::Orbit(float xoffset, float yoffset)
    {
        //m_WorldSpot

        glm::vec3 nPosCam = *Position + m_WorldSpot;
        nPosCam = glm::rotateY(nPosCam, -xoffset * m_OrbitSpeed * speedMul);
        nPosCam = glm::rotateX(nPosCam, -yoffset * m_OrbitSpeed * speedMul);
        //nPosCam = UnitaryVector(nPosCam) * distance;
        *Position = nPosCam - m_WorldSpot;

        Front = *Position + m_WorldSpot + *Position;
        UpdateCameraVectorsFromCameraSpot();

    }

    void CameraComponent::FreeLookAround(float xoffset, float yoffset)
    {
        Rotation->x += yoffset * m_FreeLookSpeed * speedMul;
        Rotation->y += xoffset * m_FreeLookSpeed * speedMul;
        UpdateRotation();
    }

    glm::vec3 CameraComponent::UnitaryVector(glm::vec3 vec)
    {
        glm::vec3 unitary = vec;
        float distance = glm::distance(vec, glm::vec3(0.0f, 0.0f, 0.0f));
        float multiplier = 1 / distance;
        unitary *= multiplier;
        if (unitary.x<0.00000001f && unitary.x > -0.00000001f)unitary.x = 0;
        if (unitary.y<0.00000001f && unitary.y > -0.00000001f)unitary.y = 0;
        if (unitary.z<0.00000001f && unitary.z > -0.00000001f)unitary.z = 0;
        return unitary;
    }

}