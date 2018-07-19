//
//  LuaScriptPanel.cpp
//  bird
//
//  Created by 汪依尘 on 7/19/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "LuaScriptPanel.hpp"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include <gtc/type_ptr.hpp>
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
        
    }
    
    void LuaScriptPanel::OnUpdate()
    {
        
    }
    
    
}
