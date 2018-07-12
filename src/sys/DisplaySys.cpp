//
//  DisplaySys.cpp
//  bird
//
//  Created by 汪依尘 on 6/9/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "DisplaySys.hpp"

#include <iostream>
#include "DisplaySys.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"

Camera* DisplaySys::Main_Camera = new Camera();

DisplaySys::DisplaySys(int h, int w, const char* t)
: height(h), width(w), title(t), window(NULL), renderer(NULL)
{
    if (Init() < 0)
    {
        std::cout<<"[ERROR]: DisplaySystem Initialization Failed."<<std::endl;
    }
}

DisplaySys::~DisplaySys()
{
    if (renderer!=NULL)
        delete renderer;
    glfwTerminate();
}

int DisplaySys::Init()
{
    renderer = new Renderer();
    
    if (!glfwInit())
    {
        std::cout<<"[GLFW]: glfwInit() failed."<<std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    std::cout<<"[GLFW]: glfw version - "<<glfwGetVersionString()<<std::endl;
    
    if((window = glfwCreateWindow(width, height, title, NULL, NULL)) == NULL)
    {
        std::cout<<"[GLFW]: glfwCreateWindow(width, height, title, NULL, NULL) failed."<<std::endl;
        getchar();
        glfwTerminate();
        return -1;
    }
    const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (vidmode->width-width)/2, (vidmode->height-height)/2);
    
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(1.f, 1.f, 1.f, 1.0f);
    GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    glDepthMask(GL_TRUE);
    return 1;
}

int DisplaySys::Update()
{
    return 1;
}

void DisplaySys::Refresh()
{
    glfwSwapBuffers(window);
}

