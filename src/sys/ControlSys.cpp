//
//  ControlSys.cpp
//  bird
//
//  Created by 汪依尘 on 6/22/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "ControlSys.hpp"
#include <iostream>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

ControlSys* ControlSys::m_Instance = NULL;

unsigned char* ControlSys::InputKeys = new unsigned char[65536]{};
bool ControlSys::IsOnUI = false;

float ControlSys::m_LastMousePositionX = 0.0f;
float ControlSys::m_LastMousePositionY = 0.0f;
float ControlSys::m_CurrMousePositionX = 0.0f;
float ControlSys::m_CurrMousePositionY = 0.0f;

float ControlSys::m_MouseScrollOffsetX = 0.0f;
float ControlSys::m_MouseScrollOffsetY = 0.0f;

ControlSys* ControlSys::GetInstance(GLFWwindow* window)
{
    if (m_Instance==NULL)
        m_Instance = new ControlSys(window);
    return m_Instance;
}

ControlSys::ControlSys(GLFWwindow* window)
:m_Window(window)
{
    glfwSetKeyCallback(window, ControlSys::InputCallBack);
    glfwSetCursorPosCallback(window, ControlSys::MousePosCallBack);
    glfwSetScrollCallback(window, ControlSys::MouseScrollCallBack);
}

ControlSys::~ControlSys()
{
    if (m_Instance!=NULL)
        delete m_Instance;
    delete []InputKeys;
}

void ControlSys::InputCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE)
    {
        if (action == GLFW_PRESS)
        {
            InputKeys[key] = (InputKeys[key]==0x00)?0x01:0x00;
            IsOnUI = !IsOnUI;
            if (IsOnUI)
            {
                delete [] InputKeys;
                InputKeys = new unsigned char[65536]{};
            }
        }
        return;
    }
    InputKeys[key] = (action==GLFW_RELEASE)?0x00:0x01;
}

void ControlSys::MousePosCallBack(GLFWwindow *window, double x, double y)
{
    if (!IsOnUI)
    {
        ControlSys::m_CurrMousePositionX = x;
        ControlSys::m_CurrMousePositionY = y;
    }
}

void ControlSys::MouseScrollCallBack(GLFWwindow *window, double offsetX, double offsetY)
{
    ControlSys::m_MouseScrollOffsetX = offsetX;
    ControlSys::m_MouseScrollOffsetY = offsetY;
}

int ControlSys::Init()
{
    return 1;
}


int ControlSys::Update()
{
    if (IsOnUI)
    {
        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else
    {
        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    return 1;
}

