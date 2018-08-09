//
//  LuaScriptPanel.cpp
//  bird
//
//  Created by 汪依尘 on 7/19/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "LuaScriptPanel.hpp"
#include "Operations.hpp"
#include "ResourceManager.hpp"

namespace gui {
    LuaScriptPanel::LuaScriptPanel( LuaScript* luaScript)
    : m_LuaScript(luaScript)
    {
        
    }
    
    LuaScriptPanel::~LuaScriptPanel()
    {
        
    }
    
    void LuaScriptPanel::OnRender()
    {
        ImGui::CollapsingHeader(m_LuaScript->GetComponentTag());
        ImGui::Text(m_LuaScript->GetFilePath());
    }
    
    void LuaScriptPanel::OnUpdate()
    {
        
    }
    
    
}
