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

class Renderer;
class Camera;

class DisplaySys: public System
{
public:
    static Camera* Main_Camera;
    static Timer   MsPFTimer;

private:
    int height;
    int width;
    const char* title;
    GLFWwindow* window;
    Renderer* renderer;
private:
//    void ImGuiInit();
public:
    inline GLFWwindow* GetWindow() { return window; }
    inline Renderer* GetRenderer() { return renderer; }
public:
//    void NewFrame();
//    void CleanUp();
public:
    DisplaySys(int height, int width, const char* title);
    ~DisplaySys();
    int Init();
    int Update();
    void Refresh();
};

#endif /* DisplaySys_hpp */
