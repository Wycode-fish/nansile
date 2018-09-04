//
//  UI.cpp
//  bird
//
//  Created by 汪依尘 on 7/10/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "UI.hpp"
#include "MeshRendererAssimp.hpp"
#include "MeshRendererPanel.hpp"
#include "ParticleSystemPanel.hpp"
#include "LuaScript.hpp"
#include "LuaScriptPanel.hpp"

namespace gui {
    
    GuiSys* GuiSys::m_Instance = NULL;
    
    GuiSys* GuiSys::GetInstance(GLFWwindow* window)
    {
        if (m_Instance==NULL)
            m_Instance = new GuiSys(window);
        return m_Instance;
    }
    
    void GuiSys::NewFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }
    
    void GuiSys::EndFrame()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    
    GuiSys::~GuiSys()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        
        if (m_Instance!=NULL)
            delete m_Instance;
    }
    
    GuiSys::GuiSys(GLFWwindow* window)
    {
        ImGui::CreateContext();
        ImGui_ImplOpenGL3_Init();
        ImGui_ImplGlfw_InitForOpenGL(window, false);
        ImGui::StyleColorsDark();
        
        std::cout<<"register start."<<std::endl;

        ComponentPanel::Register<MeshRendererPanel, rl::MeshRenderer>("Mesh Renderer");
        if (ComponentPanel::GetPanelGenerators()["Mesh Renderer"] == nullptr)
        {
            std::cout<<"Add failed."<<std::endl;
        }
        
        ComponentPanel::Register<ParticleSystemPanel, ParticleSystem>("Particle System");
        if (ComponentPanel::GetPanelGenerators()["Particle System"] == nullptr)
        {
            std::cout<<"Add failed."<<std::endl;
        }
        
        ComponentPanel::Register<LuaScriptPanel, LuaScript>("Lua Script");
        if (ComponentPanel::GetPanelGenerators()["Lua Script"] == nullptr)
        {
            std::cout<<"Add failed."<<std::endl;
        }
        // Waiting for more component panels...
    }
    
    void Gui::ShowHelpMarker(const char *desc)
    {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip(desc);

    }
};
