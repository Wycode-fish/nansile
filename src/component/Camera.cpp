//
//  Camera.cpp
//  bird
//
//  Created by 汪依尘 on 7/1/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Camera.hpp"
#include "ControlSys.hpp"
#include <utility>
#include "GLFW/glfw3.h"

glm::mat4 Camera::DefaultProjectionMatrix = glm::perspective(glm::radians(45.0f), 16.0f/9.0f, 0.01f, 100.0f);
glm::mat4 Camera::OrthographicProjectionMatrix = glm::ortho(-VWidth, VWidth, -VHeight, VHeight, -5.0f, 5.0f);
glm::mat4 Camera::PerspectiveProjectionMatrix = glm::perspective(glm::radians(45.0f), 16.0f/9.0f, 0.01f, 100.0f);

Camera::Camera()
: GameObject("Camera"), m_CameraMovingSpeed(5.f), m_MouseMovingSensitivity(0.05f), m_DeltaTimer(Timer::DeltaClock()), m_SkyBox(NULL), m_Proj(Camera::DefaultProjectionMatrix), m_FOV(45.0f)
{
    m_ViewMatUpdate();
    GetTransform()->SetRotation(glm::vec3(0.0f, 0.0f, -1.0f));
}

Camera::~Camera()
{
    if (m_SkyBox!=NULL)
        delete m_SkyBox;
}

void Camera::OnRender()
{
    if (m_SkyBox!=NULL)
        m_SkyBox->OnRender();
}

void Camera::Update()
{
    m_KeyUpdate();
    m_MouseUpdate();
    m_ViewMatUpdate();
    m_ProjMatUpdate();
}

void Camera::m_KeyUpdate()
{
    m_CameraMovingSpeed = 5.f * m_DeltaTimer.GetDelta();
    glm::vec3 currPosition = GetTransform()->GetPosition();
    if (ControlSys::InputKeys[GLFW_KEY_W])
        GetTransform()->SetPosition(currPosition + m_CameraMovingSpeed * GetTransform()->GetForward());
    if (ControlSys::InputKeys[GLFW_KEY_S])
        GetTransform()->SetPosition(currPosition - m_CameraMovingSpeed * GetTransform()->GetForward());
    if (ControlSys::InputKeys[GLFW_KEY_A])
        GetTransform()->SetPosition(currPosition - m_CameraMovingSpeed * GetTransform()->GetRight());
    if (ControlSys::InputKeys[GLFW_KEY_D])
        GetTransform()->SetPosition(currPosition + m_CameraMovingSpeed * GetTransform()->GetRight());
}

void Camera::m_MouseUpdate()
{
    auto lastPosition = ControlSys::GetLastMousePosition();
    auto currPosition = ControlSys::GetCurrMousePosition();
    
    float offsetX = (lastPosition.first - currPosition.first);
    float offsetY = (lastPosition.second - currPosition.second);
    if (offsetX == 0.0f && offsetY == 0.0f)
        return;
    
    offsetX = offsetX * m_MouseMovingSensitivity;
    offsetY = offsetY * m_MouseMovingSensitivity;
    
    m_Pitch += offsetY;
    m_Yaw += offsetX;
    
    if (m_Pitch>89.0f) m_Pitch = 89.0f;
    if (m_Pitch<-89.0f) m_Pitch = -89.0f;
    
    glm::vec3 front;
    front.x = - sin(glm::radians(m_Yaw));
    front.y =   sin(glm::radians(m_Pitch));
    front.z = - cos(glm::radians(m_Pitch)) * cos(glm::radians(m_Yaw));

    GetTransform()->SetRotation(glm::normalize(front));
    
    ControlSys::SyncMousePosition();
}

void Camera::m_ViewMatUpdate()
{
    m_View = glm::lookAt(GetTransform()->GetPosition(), GetTransform()->GetPosition() + GetTransform()->GetForward(), Transform::Up);
}

void Camera::m_ProjMatUpdate()
{
    //  ----- FOV Update() ----- //
    m_FOV += ControlSys::GetMouseScrollOffset().second * 0.2f;
    if (m_FOV < 1.0f) m_FOV = 1.0f;
    if (m_FOV > 89.0f) m_FOV = 89.0f;
    m_Proj = glm::perspective(glm::radians(m_FOV), VWidth/VHeight, 0.01f, 100.0f);
    
    ControlSys::ResetScrollOffset();
}

void Camera::SetFOV(const float& fov)
{
    m_FOV = fov;
    
}

