//
//  UI.hpp
//  bird
//
//  Created by 汪依尘 on 7/10/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef UI_hpp
#define UI_hpp

#include <stdio.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace gui {
    class GuiSys
    {
    public:
        static GuiSys* GetInstance(GLFWwindow* window);
        ~GuiSys();
    public:
        void NewFrame();
        void Update();
    private:
        static GuiSys* m_Instance;
    private:
        GuiSys(GLFWwindow* window);
        GuiSys(const GuiSys&) = delete;
        GuiSys& operator=(const GuiSys&) = delete;
    };
    
    class Gui
    {
    public:
        static void ShowHelpMarker(const char* desc);
    public:
        Gui(){}
        virtual ~Gui() {}
    public:
        virtual void OnUpdate() {}
        virtual void OnRender() {}
    };
};
#endif /* UI_hpp */
