//
//  LuaScriptPanel.hpp
//  bird
//
//  Created by 汪依尘 on 7/19/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef LuaScriptPanel_hpp
#define LuaScriptPanel_hpp

#include <stdio.h>
#include "LuaScript.hpp"
#include "GameObjectPanel.hpp"

namespace gui {
    
    class LuaScriptPanel: public ComponentPanel
    {
    public:
        LuaScriptPanel(LuaScript* luaScript);
        ~LuaScriptPanel();
    public:
        void OnRender();
        void OnUpdate();
    public:
        inline void BindLuaScript(LuaScript* luaScript) { m_LuaScript = luaScript; }
        inline void BindComponent(Component* component) { m_LuaScript = dynamic_cast<LuaScript*>(component);}
    private:
        LuaScript* m_LuaScript;
    };
};


#endif /* LuaScriptPanel_hpp */
