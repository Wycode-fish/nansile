//
//  ControlSys.hpp
//  bird
//
//  Created by 汪依尘 on 6/22/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef ControlSys_hpp
#define ControlSys_hpp

#include <stdio.h>
#include <utility>
#include "System.h"
#define KEYDOWN 0x01
#define KEYUP   0x00

class GLFWwindow;

class ControlSys: public System
{
public:
    ~ControlSys();
    int Init();
    int Update();
public:
    static ControlSys* GetInstance(GLFWwindow* window);
public:
    static unsigned char* InputKeys;
    static bool IsOnUI;
    static inline std::pair<float, float> GetLastMousePosition() { return std::make_pair(m_LastMousePositionX, m_LastMousePositionY);}
    static inline std::pair<float, float> GetCurrMousePosition() { return std::make_pair(m_CurrMousePositionX, m_CurrMousePositionY);}
    static inline std::pair<float, float> GetMouseScrollOffset() { return std::make_pair(m_MouseScrollOffsetX, m_MouseScrollOffsetY); }
    static inline void ResetScrollOffset() { m_MouseScrollOffsetX = 0.0f;  m_MouseScrollOffsetY = 0.0f;}
    static inline void SyncMousePosition() { m_LastMousePositionX = m_CurrMousePositionX; m_LastMousePositionY = m_CurrMousePositionY;}
    
public:
    static void InputCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MousePosCallBack(GLFWwindow* window, double x, double y);
    static void MouseScrollCallBack(GLFWwindow* window, double x, double y);
    
public:
    static float m_LastMousePositionX, m_LastMousePositionY;
    static float m_CurrMousePositionX, m_CurrMousePositionY;
    static float m_MouseScrollOffsetX, m_MouseScrollOffsetY;

private:
    static ControlSys* m_Instance;
    ControlSys() = delete;
    ControlSys(GLFWwindow* window);
    ControlSys& operator=(const ControlSys&) = delete;
    ControlSys(const ControlSys&) = delete;

private:
    GLFWwindow* m_Window;
};
#endif /* ControlSys_hpp */
