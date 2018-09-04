//
//  DisplaySys.hpp
//  bird
//
//  Created by 汪依尘 on 6/9/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef DisplaySys_hpp
#define DisplaySys_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "System.h"
#include "Timer.hpp"

namespace rl {
    class Renderer;
}
class Camera;

class DisplaySys: public System
{
public:
    static DisplaySys* GetInstance(unsigned height = 0, unsigned weight = 0, const char* name = "");
    
public:
    inline unsigned GetHeight() const { return m_Height; }
    inline unsigned GetWidth() const { return m_Width; }
    inline float    GetWinHWRatio() const { return static_cast<float>(m_Height) / static_cast<float>(m_Width); }
    inline Camera*  GetMainCamera() const { return m_MainCamera; }
    inline Timer*   GetTimer() { return &m_MsPFTimer; }
    
private:
    Camera* m_MainCamera;
    Timer   m_MsPFTimer;
    
private:
    unsigned m_Height;
    unsigned m_Width;
    const char* title;
    GLFWwindow* window;
    rl::Renderer* renderer;

public:
    inline GLFWwindow* GetWindow() { return window; }
    inline rl::Renderer* GetRenderer() { return renderer; }

public:
    ~DisplaySys();
    int Init();
    int Update();
    void Refresh();
    
private:
    static DisplaySys* m_Instance;
    DisplaySys(unsigned height = 0, unsigned width = 0, const char* title = "");
};

#endif /* DisplaySys_hpp */
